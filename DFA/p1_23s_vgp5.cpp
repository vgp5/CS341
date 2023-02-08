//#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
/*
Please use g++-12 -Wall p1_23s_vgp5.cpp -o prog to run the program as 
any version of gcc below will result in syntax error...

*/

using namespace std;

// Print Student Information

void printStudentInfo(){
	cout << 
		"____________________________________________\n"
		"Project 1 for CS 341\n" 
		"Section number: 003 \n"
		"Semester: Spring 2023 \n"
		"Written by: Vashu Patel \n"
		"Instructor: Marvin Nakayama \n"
		"____________________________________________\n";
};

// Initialize the set of valid characters to check input

set<char> initValidChars(){
	set<char> s = {'.', '@'};
	for (char ch = 'a'; ch <= 'z'; ch++)
		s.insert(ch);
	for (char ch = '0'; ch <= '9'; ch++)
		s.insert(ch);
	return s;
};

set<char> valid_chars = initValidChars();

typedef enum State {
	Q0, Q1, Q2, Q3, Q4, Q5,
	Q6, Q7, Q8, Q9, Q10, 
	QTRAP	
} State;

class DFA {
public:
	DFA() : state(Q0) {}
	~DFA(){}
	
	void reset();
	bool validate(string s);

private:
	State state;

	bool getNextState(string s, size_t i=0);
};




int main(){
	
   	// prints student and course information and runs the DFA on user inputs

   
   printStudentInfo();

	DFA dfa;

	string yesno = "y";
	
	while (yesno == "y"){
		cout << "Do you want to enter a string? (y/n): ";
		cin >> yesno;
		cout << "\n";

		transform(yesno.begin(), yesno.end(), yesno.begin(), ::tolower); //change the input to lower if its capital

		if (yesno == "y" or yesno == "yes"){
			string input;
			cout << "Please enter the string to process: ";
			cin >> input;
			
			transform(input.begin(), input.end(), input.begin(), ::tolower);
			cout << input << "\n";

			bool res = dfa.validate(input);
			cout << input;
			(res) ? cout << " is valid" : cout << " is not valid";
			cout << "\n";
		} else {
			cout << "Quitting the Program!\n";
			exit(EXIT_SUCCESS);
		}
		cout << "----------------------------------\n";
		dfa.reset();
	}
}

//Organized the states using a map and maps the state using their string representation

map<State, string> state_str = {
	{Q0, "Q0"}, {Q1, "Q1"}, {Q2, "Q2"}, {Q3, "Q3"}, {Q4, "Q4"}, 
	{Q5, "Q5"}, {Q6, "Q6"}, {Q7, "Q7"}, {Q8, "Q8"}, {Q9, "Q9"},
	{Q10, "Q10"}, {QTRAP, "QTRAP"}
};

string stateToString(State s){ return state_str[s]; } // returns the string representation of a state

bool DFA::validate(string s){ return getNextState(s); }

void DFA::reset(){ state = Q0; }

bool DFA::getNextState(string s, size_t i){
	char ch = s[i];

	if (i == s.size())
		return (state == Q7);

	if (find(valid_chars.begin(), valid_chars.end(), ch) == valid_chars.end()){
		cout << "Found invalid char " << ch << "\n";
		state = QTRAP;
	}
	
   /*
   The switch cases below start reading the string from input at Q0, 
   checks for the standard @edu requirements if its valid and begin 
   the transformation as per the DFA model
   
   
   */
   
   
   switch(state){
		case Q0: 
			cout << " : Q0 (Start)\n";
			state = (not isalpha(ch)) ? QTRAP : Q1;
			break;
		case Q1:
			if (not isalnum(ch)){
				switch(ch){
					case '@':
						state = Q2;
						ch = ' '; 
						break;
					case '.':
						state = Q8; 
						break;
					default:
						state = QTRAP;
						break;
				}
			}
		
			break;
		case Q2:
			
			state = (isalpha(ch)) ? Q3 : QTRAP;
			break;
		case Q3:
			
			if (not isalnum(ch))
				state = (ch == '.') ? Q4 : QTRAP;
			
			break;
		case Q4:
			
			if (not isalpha(ch))
				state = QTRAP;
			else
				state = (ch == 'e') ? Q5 : Q10;
			break;
		case Q5:
			
			if (ch == 'd')
				state = Q6;
			else if (isalnum(ch))
				state = Q10;
			else if (ch == '.')
				state = Q4;
			else
				state = QTRAP;
			break;
		case Q6:
			
			if (ch == 'u')
				state = Q7;
			else if (isalnum(ch))
				state = Q10;
			else if (ch == '.')
				state = Q4;
			else
				state = QTRAP;
			break;
		case Q7:
			
			state = (ch == '.') ? Q4 : Q10;
			break;
		case Q8:
			
			state = (isalpha(ch)) ? Q9 : QTRAP;
			break;
		case Q9:
			if (not isalnum(ch)){
				switch(ch){
					case '.':
						state = Q1;
						break;
					case '@':
						state = Q2;
						ch = ' '; 
						break;
					default:
						state = QTRAP;
						break;
				}
			} 
		
			break;
		case Q10:
			if (ch == '.')
				state = Q4;
		
			break;
		case QTRAP: 
			
			break;
		default:
			cerr << "Error: Invalid state " << state << "\n";
			break;
	}

	(ch == ' ') ? cout << "@: " : cout << ch << ": "; 
	cout << stateToString(state) << "\n";
	
	
	if (ch == '@')
		state = QTRAP;
	return getNextState(s, i+1);
}



