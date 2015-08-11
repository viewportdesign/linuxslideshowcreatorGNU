// SlideshowCreator (input path with pictures in it) -> Output .xml file which can be taken in Linux(e.g. Ubuntu) to use automatic slideshows on the desktop
// Programmer:Daniel Resch
// Programmer:

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>


using namespace std;

// This method simply checks if the extension is an image file
// I know there's a var.find(..) method to apply this, but for some reasons this didn't work
// Method could also improved further, because if theres a .jpg directly inside the file name it won't work either

void createXML(int numpics, string pictures[50], char* path);

bool isPicture(string name)
{

int size = name.length();


for(int i = 0; i < size; i++)
{
    if(name[i] == '.')
    {

     if( (i+3) <= size)
     {
         // Check the extension to be an image
         if(name[i+1] == 'j' && name[i+2] == 'p' && name[i+3] == 'g') return true;

         if(name[i+1] == 'p' && name[i+2] == 'n' && name[i+3] == 'g') return true;

         if(name[i+1] == 'g' && name[i+2] == 'i' && name[i+3] == 'f') return true;

     }

    }

}

return false;

}








int main()
{
    cout << "Slideshow Creator 0.1 alpha" << endl;

    cout << "Please input path of located pictures!" << endl;


  char path[256] = "";

  char name[256] = "";

  string pictures[50];

  cin >> path;

  int numpics = 0;


  DIR *directory;
  struct dirent *file;
  directory = opendir(path);
  while (file = readdir(directory))
{

    for(int i = 0; i < sizeof(file->d_name); i++)
    {
        name[i] = file->d_name[i];
    }


        if(isPicture(string (name)))
        {

        cout << file << endl;
         pictures[numpics] = string(name);
         numpics++;

        }







}


// Testing Purposes
cout << "Output of all Pictures" << endl;


for(int i = 0; i < numpics; i++)
{
 cout << pictures[i] << endl;
}

// Now the writing process


createXML(numpics,pictures,path);






    return 0;
}



void createXML(int numpics, string pictures[50], char* path)
{


   char data[256];
   ofstream outfile;
   outfile.open("slideshow.xml");
   cout << "Writing to the file" << endl;

   // XML-Header Tag Definitions

   outfile << "<background>" << endl << "<starttime>" << endl << "<year>2009</year>" << endl << "<month>08</month>" << endl
   << "<day>04</day>" << endl << "<hour>00</hour>" << endl << "<minute>00</minute>" << endl << "<second>00</second>" << endl
   << "</starttime>" << endl << "<!-- This animation will start at midnight. -->" << endl;




    for(int i = 0; i < numpics-1; i++)
    {

        // The File
           outfile << "<static>" << endl;
            outfile << "<duration>1795.0</duration>" << endl;
            outfile << "<file>" <<path<<"/"<< pictures[i] << "</file>" << endl;
            outfile << "</static>" << endl;

        // The Transition
            outfile << "<transition>" << endl;
           outfile << "<duration>5.0</duration>" << endl;
           outfile << "<from>"<<path<<"/"<<pictures[i] << "</from>" << endl;
           outfile << "<to>"<<path<<"/"<<pictures[i+1]<<"</to>" << endl;
           outfile << "</transition>" << endl;

    }

// Close the XML,Header

outfile << "</background>" << endl;



   outfile.close();


cout << "File successfully created!" << endl;

}
