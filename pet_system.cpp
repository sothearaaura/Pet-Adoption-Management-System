#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;
class Pet {
public:
    int id;
    string name;
    string species;
    string breed;
    int age;
    string gender;
    string status; 
    string description;
    Pet() : id(0), age(0) {}
    Pet(int petId, string petName, string petSpecies, string petBreed, 
        int petAge, string petGender, string petDescription) 
        : id(petId), name(petName), species(petSpecies), breed(petBreed),
          age(petAge), gender(petGender), status("Available"), description(petDescription) {}
    string toString() const {
        return to_string(id) + "," + name + "," + species + "," + breed + "," + 
               to_string(age) + "," + gender + "," + status + "," + description;
    }
    static Pet fromString(const string& str) {
        Pet pet;
        stringstream ss(str);
        string item;
        getline(ss, item, ','); pet.id = stoi(item);
        getline(ss, pet.name, ',');
        getline(ss, pet.species, ',');
        getline(ss, pet.breed, ',');
        getline(ss, item, ','); pet.age = stoi(item);
        getline(ss, pet.gender, ',');
        getline(ss, pet.status, ',');
        getline(ss, pet.description);
        return pet;
    }
    void display() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Species: " << species << endl;
        cout << "Breed: " << breed << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Gender: " << gender << endl;
        cout << "Status: " << status << endl;
        cout << "Description: " << description << endl;
        cout << "------------------------" << endl;
    }
};
class Adopter {
public:
    int id;
    string name;
    string phone;
    string email;
    string address;
    string preferredSpecies;
    Adopter() : id(0) {}
    Adopter(int adopterId, string adopterName, string adopterPhone, 
            string adopterEmail, string adopterAddress, string preferred)
        : id(adopterId), name(adopterName), phone(adopterPhone),
          email(adopterEmail), address(adopterAddress), preferredSpecies(preferred) {}
    string toString() const {
        return to_string(id) + "," + name + "," + phone + "," + email + "," + 
               address + "," + preferredSpecies;
    }
    static Adopter fromString(const string& str) {
        Adopter adopter;
        stringstream ss(str);
        string item;
        getline(ss, item, ','); adopter.id = stoi(item);
        getline(ss, adopter.name, ',');
        getline(ss, adopter.phone, ',');
        getline(ss, adopter.email, ',');
        getline(ss, adopter.address, ',');
        getline(ss, adopter.preferredSpecies);
        return adopter;
    }
    void display() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "Address: " << address << endl;
        cout << "Preferred Species: " << preferredSpecies << endl;
        cout << "------------------------" << endl;
    }
};
class AdoptionRequest {
public:
    int requestId;
    int petId;
    int adopterId;
    string status; 
    string requestDate;
    AdoptionRequest() : requestId(0), petId(0), adopterId(0) {}
    AdoptionRequest(int reqId, int pId, int aId, string date)
        : requestId(reqId), petId(pId), adopterId(aId), status("Pending"), requestDate(date) {}
    string toString() const {
        return to_string(requestId) + "," + to_string(petId) + "," + 
               to_string(adopterId) + "," + status + "," + requestDate;
    }
    static AdoptionRequest fromString(const string& str) {
        AdoptionRequest request;
        stringstream ss(str);
        string item;
        getline(ss, item, ','); request.requestId = stoi(item);
        getline(ss, item, ','); request.petId = stoi(item);
        getline(ss, item, ','); request.adopterId = stoi(item);
        getline(ss, request.status, ',');
        getline(ss, request.requestDate);
        return request;
    }
};
class PetAdoptionSystem {
private:
    vector<Pet> pets;
    vector<Adopter> adopters;
    vector<AdoptionRequest> requests;
    int nextPetId;
    int nextAdopterId;
    int nextRequestId;
public:
    PetAdoptionSystem() : nextPetId(1), nextAdopterId(1), nextRequestId(1) {
        loadData();
    }
    ~PetAdoptionSystem() {
        saveData();
    }
    void saveData() {
        ofstream petFile("pets.csv");
        for (const auto& pet : pets) {
            petFile << pet.toString() << endl;
        }
        petFile.close();
        ofstream adopterFile("adopters.csv");
        for (const auto& adopter : adopters) {
            adopterFile << adopter.toString() << endl;
        }
        adopterFile.close();
        ofstream requestFile("requests.csv");
        for (const auto& request : requests) {
            requestFile << request.toString() << endl;
        }
        requestFile.close();
        ofstream idFile("ids.csv");
        idFile << nextPetId << "," << nextAdopterId << "," << nextRequestId << endl;
        idFile.close();
    }
    void loadData() {
        ifstream petFile("pets.csv");
        string line;
        while (getline(petFile, line) && !line.empty()) {
            pets.push_back(Pet::fromString(line));
        }
        petFile.close();
        ifstream adopterFile("adopters.csv");
        while (getline(adopterFile, line) && !line.empty()) {
            adopters.push_back(Adopter::fromString(line));
        }
        adopterFile.close();
        ifstream requestFile("requests.csv");
        while (getline(requestFile, line) && !line.empty()) {
            requests.push_back(AdoptionRequest::fromString(line));
        }
        requestFile.close();
        ifstream idFile("ids.csv");
        if (getline(idFile, line) && !line.empty()) {
            stringstream ss(line);
            string item;
            getline(ss, item, ','); nextPetId = stoi(item);
            getline(ss, item, ','); nextAdopterId = stoi(item);
            getline(ss, item, ','); nextRequestId = stoi(item);
        }
        idFile.close();
    }
    void addPet() {
        int numPets;
        cout << "How many pets would you like to add? ";
        cin >> numPets;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        for (int i = 0; i < numPets; i++) {
            string name, species, breed, gender, description;
            int age;
            cout << "\n--- Adding Pet " << (i + 1) << " of " << numPets << " ---" << endl;
            cout << "Enter pet name: "; getline(cin, name);
            cout << "Enter species (Dog/Cat/Bird/etc.): "; getline(cin, species);
            cout << "Enter breed: "; getline(cin, breed);
            cout << "Enter age: "; cin >> age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter gender (Male/Female): "; getline(cin, gender);
            cout << "Enter description: "; getline(cin, description);
            Pet newPet(nextPetId++, name, species, breed, age, gender, description);
            pets.push_back(newPet);
            cout << "Pet added successfully with ID: " << newPet.id << endl;
        }
        cout << "\nAll " << numPets << " pets have been added successfully!" << endl;
    }
    void displayAllPets() {
        if (pets.empty()) {
            cout << "No pets in the system." << endl;
            return;
        }
        cout << "\n=== ALL PETS ===" << endl;
        for (const auto& pet : pets) {
            pet.display();
        }
    }
    void displayAvailablePets() {
        cout << "\n=== AVAILABLE PETS ===" << endl;
        bool found = false;
        for (const auto& pet : pets) {
            if (pet.status == "Available") {
                pet.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No pets available for adoption." << endl;
        }
    }
    void searchPets() {
        int choice;
        cout << "\nSearch by:" << endl;
        cout << "1. Species" << endl;
        cout << "2. Breed" << endl;
        cout << "3. Age Range" << endl;
        cout << "4. Name" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        bool found = false;
        switch (choice) {
            case 1: {
                string species;
                cout << "Enter species: ";cin.ignore();getline(cin, species);
                for (const auto& pet : pets) {
                    if (pet.species == species && pet.status == "Available") {
                        pet.display();
                        found = true;
                    }
                }
                break;
            }
            case 2: {
                string breed;
                cout << "Enter breed: ";cin.ignore();getline(cin, breed);
                for (const auto& pet : pets) {
                    if (pet.breed == breed && pet.status == "Available") {
                        pet.display();
                        found = true;
                    }
                }
                break;
            }
            case 3: {
                int minAge, maxAge;
                cout << "Enter minimum age: ";cin >> minAge;
                cout << "Enter maximum age: ";cin >> maxAge;
                for (const auto& pet : pets) {
                    if (pet.age >= minAge && pet.age <= maxAge && pet.status == "Available") {
                        pet.display();
                        found = true;
                    }
                }
                break;
            }
            case 4: {
                string name;
                cout << "Enter pet name: ";cin.ignore();getline(cin, name);
                for (const auto& pet : pets) {
                    if (pet.name == name) {
                        pet.display();
                        found = true;
                    }
                }
                break;
            }
        }
        if (!found) {
            cout << "No pets found matching your criteria." << endl;
        }
    }
    void updatePet() {
        int petId;
        cout << "Enter pet ID to update: ";cin >> petId;
        auto it = find_if(pets.begin(), pets.end(), 
                         [petId](const Pet& p) { return p.id == petId; });
        if (it == pets.end()) {
            cout << "Pet not found!" << endl;
            return;
        }
        cout << "Current pet details:" << endl;
        it->display();
        cout << "Enter new details (press Enter to keep current value):" << endl;
        string input;
        cin.ignore();
        cout << "Name (" << it->name << "): ";getline(cin, input);
        if (!input.empty()) it->name = input;
        cout << "Species (" << it->species << "): ";getline(cin, input);
        if (!input.empty()) it->species = input;
        cout << "Breed (" << it->breed << "): ";getline(cin, input);
        if (!input.empty()) it->breed = input;
        cout << "Age (" << it->age << "): ";getline(cin, input);
        if (!input.empty()) it->age = stoi(input);
        cout << "Gender (" << it->gender << "): ";getline(cin, input);
        if (!input.empty()) it->gender = input;
        cout << "Description (" << it->description << "): ";getline(cin, input);
        if (!input.empty()) it->description = input;
        cout << "Pet updated successfully!" << endl;
    }
    void registerAdopter() {
        string name, phone, email, address, preferred;
        cout << "Enter adopter name: ";cin.ignore();getline(cin, name);
        cout << "Enter phone: ";getline(cin, phone);
        cout << "Enter email: ";getline(cin, email);
        cout << "Enter address: ";getline(cin, address);
        cout << "Enter preferred species: ";getline(cin, preferred);
        Adopter newAdopter(nextAdopterId++, name, phone, email, address, preferred);
        adopters.push_back(newAdopter);
        cout << "Adopter registered successfully with ID: " << newAdopter.id << endl;
    }
    void displayAllAdopters() {
        if (adopters.empty()) {
            cout << "No adopters registered." << endl;
            return;
        }
        cout << "\n=== ALL ADOPTERS ===" << endl;
        for (const auto& adopter : adopters) {
            adopter.display();
        }
    }
    void submitAdoptionRequest() {
        int petId, adopterId;
        cout << "Enter pet ID: ";cin >> petId;
        cout << "Enter adopter ID: ";cin >> adopterId;
        auto petIt = find_if(pets.begin(), pets.end(),
                            [petId](const Pet& p) { return p.id == petId; });
        if (petIt == pets.end()) {
            cout << "Pet not found!" << endl;
            return;
        }
        if (petIt->status != "Available") {
            cout << "Pet is not available for adoption!" << endl;
            return;
        }
        auto adopterIt = find_if(adopters.begin(), adopters.end(),
                               [adopterId](const Adopter& a) { return a.id == adopterId; });
        if (adopterIt == adopters.end()) {
            cout << "Adopter not found!" << endl;
            return;
        }
        AdoptionRequest newRequest(nextRequestId++, petId, adopterId, "2024-01-01");
        requests.push_back(newRequest);
        petIt->status = "Pending";
        cout << "Adoption request submitted successfully with ID: " << newRequest.requestId << endl;
    }
    void displayAdoptionRequests() {
        if (requests.empty()) {
            cout << "No adoption requests." << endl;
            return;
        }
        cout << "\n=== ADOPTION REQUESTS ===" << endl;
        for (const auto& request : requests) {
            cout << "Request ID: " << request.requestId << endl;
            cout << "Pet ID: " << request.petId << endl;
            cout << "Adopter ID: " << request.adopterId << endl;
            cout << "Status: " << request.status << endl;
            cout << "Date: " << request.requestDate << endl;
            cout << "------------------------" << endl;
        }
    }
    void processAdoptionRequest() {
        int requestId;
        cout << "Enter adoption request ID: ";cin >> requestId;
        auto requestIt = find_if(requests.begin(), requests.end(),
                               [requestId](const AdoptionRequest& r) { return r.requestId == requestId; });
        if (requestIt == requests.end()) {
            cout << "Adoption request not found!" << endl;
            return;
        }
        if (requestIt->status != "Pending") {
            cout << "Request already processed!" << endl;
            return;
        }
        int choice;
        cout << "1. Approve" << endl;
        cout << "2. Reject" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            requestIt->status = "Approved";
            auto petIt = find_if(pets.begin(), pets.end(),
                               [requestIt](const Pet& p) { return p.id == requestIt->petId; });
            if (petIt != pets.end()) {
                petIt->status = "Adopted";
            }
            cout << "Adoption request approved!" << endl;
        } else if (choice == 2) {
            requestIt->status = "Rejected";
            auto petIt = find_if(pets.begin(), pets.end(),
                               [requestIt](const Pet& p) { return p.id == requestIt->petId; });
            if (petIt != pets.end()) {
                petIt->status = "Available";
            }
            cout << "Adoption request rejected!" << endl;
        }
    }
    void displayMenu() {
        cout << "\n=== PET ADOPTION MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Add Pet" << endl;
        cout << "2. Display All Pets" << endl;
        cout << "3. Display Available Pets" << endl;
        cout << "4. Search Pets" << endl;
        cout << "5. Update Pet" << endl;
        cout << "6. Register Adopter" << endl;
        cout << "7. Display All Adopters" << endl;
        cout << "8. Submit Adoption Request" << endl;
        cout << "9. Display Adoption Requests" << endl;
        cout << "10. Process Adoption Request" << endl;
        cout << "11. Save and Exit" << endl;
        cout << "Enter your choice: ";
    }
    void run() {
        int choice;
        do {
            displayMenu();cin >> choice;
            switch (choice) {
                case 1:
                    addPet();
                    break;
                case 2:
                    displayAllPets();
                    break;
                case 3:
                    displayAvailablePets();
                    break;
                case 4:
                    searchPets();
                    break;
                case 5:
                    updatePet();
                    break;
                case 6:
                    registerAdopter();
                    break;
                case 7:
                    displayAllAdopters();
                    break;
                case 8:
                    submitAdoptionRequest();
                    break;
                case 9:
                    displayAdoptionRequests();
                    break;
                case 10:
                    processAdoptionRequest();
                    break;
                case 11:
                    saveData();
                    cout << "Data saved. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 11);
    }
};
int main() {
    PetAdoptionSystem system;
    system.run();
    return 0;
}