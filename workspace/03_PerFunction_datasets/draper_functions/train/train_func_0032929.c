newManager()
{
    ifstream fin("managers.dat", ios::binary);

    char UName[16], UPwd[16];
    char* UPwdHash;
    ManagerPacket Check, NewManager;
    int flag = 1;

    cout << "Enter new username : ";
    cin.ignore();
    cin.get(UName, 16);

    if (fin) {
        while (!fin.eof()) {
            fin.read((char*)&Check, sizeof(Check));
            Decrypt(Check.UsrName, SYS_PASSWORD.c_str());
            if (!strcmp(Check.UsrName, UName)) {
                flag = 0;
                break;
            }
        }
    }

    fin.close();
    ofstream fout("managers.dat", ios::binary | ios::ate);

    if (flag) {
        cout << "Enter new Password : ";
        cin.ignore();
        cin.get(UPwd, 16);
        UPwdHash = hashFunction.HashDigest(UPwd, 64);

        Encrypt(UName, SYS_PASSWORD.c_str());

        strcpy(NewManager.UsrName, UName);
        strcpy(NewManager.PwdHash, UPwdHash);

        NewManager.App.changePersDetails();

        Encrypt((char*)&NewManager.App, SYS_PASSWORD.c_str(), sizeof(Manager));

        fout.write((char*)&NewManager, sizeof(ManagerPacket));

        cout << "New Manager User created succesfully! Please login to continue." << endl;

        delete[] UPwdHash;
    } else {
        cout << "Username already exists" << endl;
        newManager();
    }

    fout.close();
}
