#include<iostream> // 2019504

using namespace std; // Syed Nazim Shah

template < class x >
class array{ // making a base class array
	private:
		x arr[3]; // making array of template class 
	public:
		array(){arr[0]=arr[1]=arr[2]=0;} // intializing array
		
		insertvalue( int index, x value){  // putting value in array
			arr[index]=value;
		}
		x returnvalue(int index){
			return this->arr[index]; // getting value of array
		}
		x *returnaddress(int index){ // getting address of array element
			return &this->arr[index];
		}
		void displayarray(){
			for (int i = 0; i < 3; i++) // displaying array
            cout << arr[i] << " ";
		 } 
};



template < class x >
  class LRU : public array<x> { // inheriting from base class to least recently used class
    private:
    x * leastrecent; // two pointer to point at recent locations 
    x * mostrecent;
    public:
      LRU() : array <x>() {leastrecent=mostrecent=NULL;} //intializing pointers

    void insert(x value) {

      for (int i = 0; i < 3; i++) { // this loop checks if the entered value already exists. if so then put that value on front
        if ( LRU::returnvalue (i) == value) { 
          x temp = LRU::returnvalue (i);
          for (int Temp = i; Temp > 0; Temp--) {
            LRU::insertvalue (Temp, LRU::returnvalue (Temp - 1));
          }
          LRU::insertvalue (0,temp);
          return;
        }
      }

      for (int i = 2; i >= 0; i--) { // if the inserted value doesnot exist in the array then it shifts the array one step forward
        LRU::insertvalue (i,LRU::returnvalue (i-1));
      }

      LRU::insertvalue (0,value); // and put value in the front

      mostrecent = LRU::returnaddress (0); // aslo pointing to the front value

      for (int i = 2; i >= 0; i--) { // this loop sets the pointer to least (in this case last) value in the array 

        if (LRU::returnvalue (i) != 0) {
          leastrecent = LRU::returnaddress (i);
          break;
        }
      }
    }

    void display() { //function to display eveything
      cout << "Most recently used Page: " << * mostrecent;
      cout << "\nLeast recently used Page: " << * leastrecent;
      cout << "\nPages in Memory Cache: ";
      LRU::displayarray();
    }

  };

template < class x >

  class LFU: public array<x> { // inheriting from base class to least frequently used class
    private:
    int frequency[3]; //array to hold frequency iterations
    public:
      LFU() : array<x> (){frequency[0] = frequency[1] = frequency[2] = 0;} // initializing 

    void insert(x value) {// function to insert value

      for (int i = 0; i < 3; i++) {
        if (LFU::returnvalue (i) == value) { //loop to check if the inserted value already exists then it iterates the frequency
          frequency[i]++;
          return;
        }
      }

      for (int i = 0; i < 3; i++) {
        if (LFU::returnvalue (i) == 0) { // if array is empty on somelocation it puts value there
          LFU::insertvalue (i, value);
          frequency[i]++;
          return;
        }
      }

      x * temp =  LFU::returnaddress (0); //intializing two temprary pointers to first location, when array is not empty and user wants to add to it
      int * temp2 = & frequency[0];

      for (int i = 0; i < 3; i++) {

        if (frequency[i] < * temp2) { // searching for lowest frequency and assigning two pointers to that location
          temp = LFU::returnaddress (i);
          temp2 = & frequency[i];
        } else if ( * temp2 == frequency[i]) { // if two frequency match 
          if (LFU::returnvalue (i) < * temp) { // the one with lowest value pointer is pointed to it
            temp = LFU::returnaddress (i);
            temp2 = & frequency[i];
          }
        }

      }
      * temp = value; // putting value on these locations
      * temp2 = 1;
    }

    void display() { // displaying everything
      cout << "\nPages in Buffer Memory: ";
      LFU::displayarray();
      cout << "\nPages Access Frequency: ";
      for (int i = 0; i < 3; i++) {
        cout << frequency[i] << " ";
      }

    }

  };

int main() { // menu driven interface 
  int choice = 0;
  cout << "\n1.Numbers(0-9)\n2.Characters (A-I) UPPER CASE ONLY****  \nPlease select a Insertion Notation that you want to use: ";
  cin >> choice;
  if (choice == 1) {
    system("CLS");
    int choice = 0;
    cout << "\n1.Least Recently Used\n2.Least Frequently Used\nPlease select a Page Replacement Mechanism: ";
    cin>>choice;
    if (choice == 1) {
      system("CLS");
      LRU < int > a1;

      while (true) {
        int x;
        cout << "\n\nEnter Page No(0 to exit): ";
        cin >> x;
        if (x <= 0|| x > 9){cout<<"\nExiting"; return 0;}
        a1.insert(x);
        a1.display();
      }
    } else if (choice == 2) {
      system("CLS");
      LFU < int > a1;

      while (true) {
        int x;
        cout << "\n\nEnter Page No(0 to exit): ";
        cin >> x;
        if (x <= 0|| x > 9){cout<<"\nExiting"; return 0;}
        a1.insert(x);
        a1.display();
      }

    } else {
      cout << "\nEnter a Valid Choice\n Exiting!!";
      return 0;
    }

  } else if (choice == 2) {
    system("CLS");
    int choice = 0;
    cout << "\n1.Least Recently Used\n2.Least Frequently Used\nPlease select a Page Replacement Mechanism: ";
    cin >> choice;
    if (choice == 1) {
      LRU < char > a1;

      while (true) {
        char x;
        cout << "\n\nEnter Page No(0 to exit): ";
        cin >> x;
        if (x == '0' || x < 'A'|| x > 'J' ){cout<<"\nExiting"; return 0;}
        a1.insert(x);
        a1.display();
      }
    } else if (choice == 2) {
      LFU < char > a1;

      while (true) {
        char x;
        cout << "\n\nEnter Page No(0 to exit): ";
        cin >> x;
        if (x == '0' || x < 'A'|| x > 'J' ){cout<<"\nExiting"; return 0;}
        a1.insert(x);
        a1.display();
      }
    } else {
      cout << "\nEnter a Valid Choice\n Exiting!!";
      return 0;
    }
  } else {
    cout << "\nEnter a Valid Choice\n Exiting!!";
    return 0;
  }

}
