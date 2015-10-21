// #include <iostream>
// #include <fstream>
// #include <string.h>
// #include <string>
// #include <sstream>
// #include <vector>
// #include <cstring>

#include "MovingAverage.h" 

using namespace std;

int MovingAverage(int startdate, int ltime, int stime, int cat, int stock) {

// int main () {

//    //get stock from hand in
//char stock[] = "PSUN";
   
//    //get current fate from hand in
//    int date = 05;
//    int month = 12;
//    int year =  2015;

//    //set integer to describe current date
//    int startdate = 130;

//    // get long length 
//    int ltime = 10;

//    //get short time
//    int stime = 5;

  // // catorogry of average (open high low close volume)
  //  int cat = 3;

   // buy sell hold command
   int x;

    stringstream ss;
    ss << stock;
    string buffer = ss.str();


   //santitse inputs
   if ( cat >5 || cat<1 ) {
     cout << "ERROR - evaluation must be in 1<=cat<=5." << endl;
     return 0; 
   }

   //append strings to get directory
   std::string filepath( "data/" );
    filepath.append( buffer );
    filepath.append("/quote.csv");


   int maxread = 50;

   string line, csvItem, item;

    vector<vector<double> > values;
    vector<double> valueline;

  ifstream myfile ( filepath );
    int lineNumber = 0;

    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            lineNumber++;
            if(lineNumber >= startdate && lineNumber <= (ltime + startdate)) {
              // cout << line << endl; 
                istringstream myline(line);
                                  istringstream in(line);
                  while (getline(in, item, ','))
                  {
                      valueline.push_back(atof(item.c_str()));
                  }

                  values.push_back(valueline);
                  valueline.clear();
            }
        }
          myfile.close();
    }

     //work out long time average 
     double currentlongav = 0.0;
     double prelongav = 0.0;
     double currentshortav = 0.0;
     double preshortav = 0.0;

     for(int i=0; i<ltime; i++){
      currentlongav = currentlongav + values[i][cat];
      prelongav = prelongav + values[i+1][cat];    
     }

     for(int j=0; j<stime; j++){
      currentshortav = currentshortav + values[j][cat];
      preshortav = preshortav + values[j+1][cat];
     }


  currentlongav = currentlongav/ltime;
  prelongav = prelongav/ltime;
  currentshortav = currentshortav/stime;
  preshortav = preshortav/stime;

  // cout << currentlongav <<"," << endl; 
  // cout << prelongav <<"," << endl; 
  // cout << currentshortav <<"," << endl; 
  // cout << preshortav <<"," << endl; 

  //now comparitive statements to issue buy or sell command

  if ( (prelongav > preshortav) && (currentlongav < currentshortav) ){
    //buy command
    cout << "buy" << endl;
    x=1;
  }
  else if ( (prelongav < preshortav) && (currentlongav > currentshortav) ){
    //sell command
    cout << "sell" << endl;
    x=-1;
  }
  else  {
      cout << "hold" << endl;
      x=0;
    }


  return x;

}


