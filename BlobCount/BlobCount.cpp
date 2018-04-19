//-----------------------------------------------------------------------------------------------------
//
// Name: Tellon Smith
//
// Course: CS 3013 - Advanced Structures and Algorithms, Spring 16, Dr. Johnson
//
// Program Assignment : #1
//
// Due Date: Thursday, Jan. 4, 2016, 2PM
//
// Purpose: This program counts the number of blobs in a 2D array. A blob is a connected group
//          of *'s (top, bottom, left or right). The program uses recursion to change the *'s to #'s.
//
//-----------------------------------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include <string>

using namespace std;

const int MAXSIZE = 22;

void openFiles(ifstream & infile, ofstream & outfile);
//Purpose: open input and ouput streams
//Requires: infile and outfile
//Returns: an opened input and output stream

void printHeading(ofstream & outfile);
//Purpose: prints headings
//Requires: opened output stream
//Returns: outfile with headings appended to it

void printWelcomeMessage(ofstream & outfile);
//Purpose: prints a welcome message
//Requires: opened output stream
//Returns: outfile with welcome message appended to it

void printExitMessage(ofstream & outfile);
//Purpose: prints an exit message
//Requires: opened output stream
//Returns: outfile with exit message appended to it

void createBorder(char(&blobWorld)[MAXSIZE][MAXSIZE]);
//Purpose: creates a border of 0's in a 2D array
//Requires: 2D array
//Returns: 2D array with a border of 0's

void readInput(ifstream & infile, char(&blobWorld)[MAXSIZE][MAXSIZE]);
//Purpose: reads the data from the input file into a 2D array
//Requires: opened input stream, 2D array
//Returns: 2D array with data from the input file

void printBlobWorld(ofstream & outfile, int blobCount, char(&blobWorld)[MAXSIZE][MAXSIZE]);
//Purpose: prints the contents of a 2D array (excluding the border)
//Requires: opened output stream, blobCount, 2D array
//Returns: outfile with contents of 2D array (excluding the border) appended to it

void countBlobs(int &blobCount, char(&blobWorld)[MAXSIZE][MAXSIZE]);
//Purpose: counts the number of blobs in the 2D array
//Requires: blobCount, 2D array
//Returns: blobCount with the number of blobs counted

void mutateBlob(int row, int col, char(&blobWorld)[MAXSIZE][MAXSIZE]);
//Purpose: recursively changes all the *'s in a blob to #'s 
//Requires: row, column, 2D array
//Returns: 2D array with all *'s replaced with #'s

void main()
{
	//variable declarations
	ifstream infile;
	ofstream outfile;
	char blobWorld[MAXSIZE][MAXSIZE];
	int blobCount = 0;

	//begin process
	openFiles(infile, outfile); //open input and output files
	printHeading(outfile);
	printWelcomeMessage(outfile);	
	readInput(infile, blobWorld); //read data from input file
	printBlobWorld(outfile, blobCount, blobWorld); //prints original blob world
	countBlobs(blobCount, blobWorld);
	printBlobWorld(outfile, blobCount, blobWorld); //prints mutated blob world
	printExitMessage(outfile);
	
	//close files 
	infile.close();
	outfile.close();

	system("pause");
}


void openFiles(ifstream & infile, ofstream & outfile)
{
	char inFileName[40];
	char outFileName[40];

	//open input stream
	cout << "\nPlease enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName);

	//display error message if the specified file cannot be opened
	if (!infile)
	{
		cout << "\nERROR: cannot open the specified file. please run the program again." << endl;
		system("pause");
		exit(1);
	}

	//open output stream
	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName);
}


void printHeading(ofstream & outfile)
{
	outfile << "\nName: Tellon Smith" << endl;
	outfile << "Course: CS 3013 - Advanced Structures and Algorithms, Spring 16, Dr. Johnson" << endl;
	outfile << "Program Assignment: #1" << endl;
	outfile << "Due Date: Thursday, Jan. 4, 2016, 2PM" << endl;
	outfile << "Purpose: This program counts the number of blobs in a 2D array. A blob is" << endl;
	outfile << "a connected group of *'s (top, bottom, left or right). The program uses" << endl;
	outfile << "recursion to change the *'s to #'s. " << endl;
}

void printWelcomeMessage(ofstream & outfile)
{
	outfile << "\nWelcome to the Blob Count Program!" << endl;
	outfile << "\n----------------------------------------------------------------------" << endl;
	outfile << "                      Blob Count Program" << endl;
	outfile << "----------------------------------------------------------------------" << endl;
}

void printExitMessage(ofstream & outfile)
{
	outfile << "\nThank you for using the Welcome to the Blob Count Program... Goodbye!" << endl;
}

void createBorder(char (&blobWorld)[MAXSIZE][MAXSIZE])
{
	//top and bottom
	for (int i = 0; i < MAXSIZE; i++)
	{
		blobWorld[0][i] = '0';
		blobWorld[21][i] = '0';
	}
	
	//left and right
	for (int i = 1; i < (MAXSIZE-1); i++)
	{
		blobWorld[i][0] = '0';
		blobWorld[i][21] = '0';
	}
	
}

void readInput(ifstream & infile, char(&blobWorld)[MAXSIZE][MAXSIZE])
{
	//create border in 2D array
	createBorder(blobWorld);

	//begin reading data into 2D array
	for (int i = 1; i < (MAXSIZE - 1); i++)
	{
		for (int j = 1; j < (MAXSIZE - 1); j++)
		{
			infile >> blobWorld[i][j];
		}
	}
}

void printBlobWorld(ofstream & outfile, int blobCount, char(&blobWorld)[MAXSIZE][MAXSIZE])
{
	//print if count = 0
	if (blobCount == 0)
	{
		outfile << "\nOriginal world:\n" << endl;
	}
	//print if count > 0
	else if (blobCount > 0)
	{
		outfile << "\nWorld with mutated blobs:\n" << endl;
	}
	
	//print 2D array (execluding border) 
	for (int i = 1; i < (MAXSIZE-1); i++)
	{
		for (int j = 1; j < (MAXSIZE-1); j++)
		{
			outfile << blobWorld[i][j] << " ";
		}
		outfile << endl;
	}
	//print if count > 0
	if (blobCount > 0)
	{
		outfile << "\n" << blobCount << " blobs were found"<< endl;
	}
}

void countBlobs(int &blobCount, char(&blobWorld)[MAXSIZE][MAXSIZE])
{
	for (int i = 1; i < (MAXSIZE - 1); i++)
	{
		for (int j = 1; j < (MAXSIZE - 1); j++)
		{
			if (blobWorld[i][j] == '*') //if value equals a "*" 
			{
				blobCount++; //increment count
				mutateBlob(i, j, blobWorld); //replace *'s to #'s
			}
		}
	}
} 

void mutateBlob(int row, int col, char(&blobWorld)[MAXSIZE][MAXSIZE])
{
	if (blobWorld[row][col] == '*') //if value equals a "*"
	{
		blobWorld[row][col] = '#'; //change to a "#"
		
		//check Surrounding values (up, down, left, right)
		mutateBlob(row-1, col, blobWorld); //check above
		mutateBlob(row+1, col, blobWorld); //check below
		mutateBlob(row, col-1, blobWorld); //check left
		mutateBlob(row, col+1, blobWorld); //check right
	}
	return;	
}