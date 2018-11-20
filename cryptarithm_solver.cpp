#include <iostream>
#include <map>

using namespace std;

string a, b, c;	// User inputs

/* 
 *  The PuzzleSolved method is used to check if the constraints have been satisfied
 *  in the CSP. This works by assessing each unique character from
 * 
 *  @param puzzle  A HASHMAP THAT HOLDS A CHARACTER REPRESENTING A UNIQUE LETTER
 *                 AND AN INTEGER THAT HOLDS THE LETTER'S VALUE IN THE CA PROBLEM
 *  @return        RETURNS TRUE IF THE CONSTRAINTS ARE MET ELSE FALSE
 */
bool puzzleSolved(map <char, int> puzzle){
	if(puzzle[a[0]] == 0 || puzzle[b[0]] == 0 || puzzle[c[0]] == 0)	
		return false;

	// Initial numerical values
	int first = 0;
	int second = 0;
	int third = 0;
 
 	// These for loops tests numbers to the letter
	for(int i = 0; i< a.length(); i++){
		first = first*10 + puzzle[a[i]];
	}
	for(int i = 0; i< b.length(); i++){
		second = second*10 + puzzle[b[i]];
	}
	for(int i = 0; i< c.length(); i++){
		third = third*10 + puzzle[c[i]];
	}

	/* If this Cryptarithmetic problem is solveable then the first and second
     entry's added values should be logically equivalent to the third entry's value.*/
	if((first + second) == third)	
		return true;
	else 
		return false;
}

/*
 *  The backtrack method is based off the pseudocode shown in the AIMA textbook.
 *  It acts as nothing more than the 'driver' of the program as it does the
 *  calculation. Whether a puzzle is a CSP and is solveable is entirely determined 
 *  by the PuzzleSolved() method. Note: this algorithm is recursive.
 *  
 *  @param  &puzzle     HASHMAP CONTAINING THE LETTER AND ITS VALUE
 *  @param  letterSet   SET OF LETTERS THAT MUST BE CHECKED BY THE ALGORITHM
 *  @param  phrase      ENTIRE PHRASE
 *  @return             USES THE PuzzleSolved() METHOD TO SEE IF THE PUZZLE IS 
 *                      COMPLETE ELSE IT CONTINUES WITH THE BACKTRACK
 */
bool backTrack(map<char, int> &puzzle, string letterSet,string fullString){
 
 	// Checks if the letterSet is empty. If so then it checks if the constraints
    // are satisfied. If the constraints are satisfied then this puzzle is solved
    // and the solution is returned.
	if(letterSet.empty()){
		return puzzleSolved(puzzle);
	}
 	
 	// Tests each digit starting from 9 then goes to 0
	for(int i = 9; i >=0; i--){
		char toAssign = letterSet[0];  // assigns the letter to be checked off
		bool present = false;

		// An iterator is used to perform the check as it will go through every
        // element in the HashMap puzzle
		for(map <char, int>::iterator it = puzzle.begin(); it != puzzle.end(); it++)
		{
			if(it->second == i){ // If the numerical value is already in use then digit is present
				present = true;	
			}
		}

		if(present == true)	// Success Case: new value
			continue;

		puzzle[toAssign] = i;

		bool b = backTrack(puzzle, letterSet.substr(1),fullString); // recursive algo
		
		if(b == true) // Success!
			return true;
		else{
			puzzle[toAssign] = -1; // default fail case
		}
	}
	return false;
}
 
int main(){
	map <char, int> puzzle;
	string letterSet;	// a string that holds every unique character in the cryptaritm set
	
	cout << "Cryptarithmetic Solver via Backtrack by Jan Ocampo" << endl;
	cout << "--------------------------------------------------" << endl;
    cout << "Form: 1st + 2nd = 3rd" << endl;
	cout << "Enter the first entry: ";
	cin >> a;
	cout << "Enter the second entry: ";
	cin >> b;
	cout << "Enter the third entry: ";
	cin >> c;
	cout << endl << "You entered: " << endl << "     " << a << endl << "+    " << b 
            << endl << "--------------" << endl << "    " << c << endl;

	int repeat[26] = {0};

	// These for loops ensure that only unique characters are placed into 'letters' 
	for(int i = 0; i< a.length(); i++){
		if(repeat[a[i]-'a']++ == 0){
			letterSet+= a[i];
		}
	}

	for(int i = 0; i< b.length(); i++){
		if(repeat[b[i]-'a']++ == 0){
			letterSet+= b[i];
		}
	}

	for(int i = 0; i< c.length(); i++){
		if(repeat[c[i]-'a']++ == 0){
			letterSet+= c[i];
		}
	}

	for(int i = 0; i < letterSet.size(); i++){
		puzzle[letterSet[i]] = -1;
	}

	bool b = backTrack(puzzle,letterSet,letterSet);
	if (b == 0)	{
		cout << "No solution because this problem doesn't satisfy CSP reqs" << endl;
	}
	else{ // print solution
		cout << endl << "Here is the solution..." << endl;
		for(map <char, int>::iterator it = puzzle.begin(); it != puzzle.end(); it++){
		cout << it->first << "----> " << it->second << endl;
		}
	}
	cout << endl;
 
}