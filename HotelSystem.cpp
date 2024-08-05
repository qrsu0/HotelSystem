/*

hotel managment system..

- user chek in for a room
- user check in for any additional needs ( include breakfast .. gym .. pool) 
- calculate the user pill for certain day

- Manager check out the rooms if empty
- Manager check in hotel income

class hotel 
-room number
- room status (full/empty)
- pill based on the room
- room type

class guest 
variables :
- guest id 
- guest name 
- guest duration

functionalities 
- setter / getter 
- using rand() for guest id

class employer 
- emp id 
- emp name
- emp role 

*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

// Creating classes 

// create class hotel
class hotel {
private:
    int room;
    bool isEmpty = true;
    int roomPrice = 100;
    string roomType;

public:
    // SETTERS
    void setRoom(int room) {
        this->room = room;
    }
    void setIsEmpty(bool isEmpty) {
        this->isEmpty = isEmpty;
    }
    void setRoomPrice(int roomPrice) {
        this->roomPrice = roomPrice;
    }
    void setRoomType(string roomType) {
        this->roomType = roomType;
    }

    // GETTERS
    int getRoom() { return room; }
    bool getIsEmpty() { return isEmpty; }
    int getRoomPrice() { return roomPrice; }
    string getRoomType() { return roomType; }
};

// create class guest
class guest {
private:
    int guestId;
    string name;
    int duration;
    vector<string> additionalNeeds;

public:
    // Setter
    void setGuestId() {
        this->guestId = rand() % 100 + 1;
    }
    void setName(string name) {
        this->name = name;
    }
    void setDuration(int duration) {
        this->duration = duration;
    }
    void addAdditionalNeed(string need) {
        this->additionalNeeds.push_back(need);
    }

    // Getter
    int getGuestId() { return guestId; }
    string getName() { return name; }
    int getDuration() { return duration; }
    vector<string> getAdditionalNeeds() { return additionalNeeds; }
};

// create class employer
class employer {
private:
    int empId;
    string empName;
    string empRole;

public:
    // Setters
    void setEmpId(int empId) {
        this->empId = empId;
    }
    void setEmpName(string empName) {
        this->empName = empName;
    }
    void setEmpRole(string empRole) {
        this->empRole = empRole;
    }

    // Getters
    int getEmpId() { return empId; }
    string getEmpName() { return empName; }
    string getEmpRole() { return empRole; }
};

// needed functions 
void mainMenu() {
    cout << "WELCOME TO X HOTEL\n";
    cout << "-\n";
    cout << "1. Check In\n";
    cout << "2. Check Out\n";
    cout << "3. Exit\n";
    cout << "CHOICE: ";
}

void checkIn(vector<hotel>& rooms, vector<guest>& guests) {
    guest newGuest;
    hotel room;
    string name;
    int duration, roomNumber, additionalChoice;
    char needMore;
    string need;

    cout << "Enter your name: ";
    cin >> name;
    newGuest.setName(name);

    cout << "Enter duration of stay (in days): ";
    cin >> duration;
    newGuest.setDuration(duration);

    newGuest.setGuestId();

    cout << "Enter room number you want to check in: ";
    cin >> roomNumber;
    room.setRoom(roomNumber);
    room.setIsEmpty(false);
    room.setRoomType("Standard");

    // Additional needs
    do {
        cout << "Do you have any additional needs? (1 for Breakfast, 2 for Gym, 3 for Pool): ";
        cin >> additionalChoice;

        switch (additionalChoice) {
        case 1:
            newGuest.addAdditionalNeed("Breakfast");
            break;
        case 2:
            newGuest.addAdditionalNeed("Gym");
            break;
        case 3:
            newGuest.addAdditionalNeed("Pool");
            break;
        default:
            cout << "Invalid choice!";
        }

        cout << "Do you have more additional needs? (y/n): ";
        cin >> needMore;
    } while (needMore == 'y' || needMore == 'Y');

    guests.push_back(newGuest);
    rooms.push_back(room);

    cout << "Check-in successful! Your Guest ID is " << newGuest.getGuestId() << endl;
}

void checkOut(vector<hotel>& rooms, vector<guest>& guests) {
    int guestId;
    bool found = false;

    cout << "Enter your Guest ID for checkout: ";
    cin >> guestId;

    for (size_t i = 0; i < guests.size(); ++i) {
        if (guests[i].getGuestId() == guestId) {
            int bill = rooms[i].getRoomPrice() * guests[i].getDuration();
            cout << "Your total bill is: $" << bill << endl;

            rooms[i].setIsEmpty(true);
            guests.erase(guests.begin() + i);
            rooms.erase(rooms.begin() + i);

            cout << "Checkout successful!" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Guest ID not found!" << endl;
    }
}

int main() {
    srand(time(0));
    vector<hotel> rooms;
    vector<guest> guests;
    int choice;

    do {
        mainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            checkIn(rooms, guests);
            break;
        case 2:
            checkOut(rooms, guests);
            break;
        case 3:
            cout << "Thank you for using X Hotel Management System!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
