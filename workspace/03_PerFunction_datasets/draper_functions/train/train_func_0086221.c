handleApplicantLogin()
{
    char uname[16], upwd[16];
    int flag = 1;
    Packet application;
    ifstream file("saved.dat", ios::binary);

    Status toSubmit;

    cout << "Enter User Name : ";
    cin.ignore();
    cin.get(uname, 16);
    cout << "Enter Password : ";
    cin.ignore();
    cin.get(upwd, 16);

    char* upwdhash = hashFunction.HashDigest(upwd, 64);

    if (file) {
        while (!file.eof()) {
            file.read((char*)&application, sizeof(Packet));
            if (!strcmp(application.PwdHash, upwdhash)) {
                Decrypt(application.UsrName, SYS_PASSWORD.c_str());
                if (!strcmp(application.UsrName, uname)) {
                    Decrypt((char*)&application.App, SYS_PASSWORD.c_str(), sizeof(Applicant));
                    toSubmit = application.App.handler();

                    if (toSubmit == SAVE)
                        application.save();
                    else {
                        application.submit();
                        application.save();
                        cout << "Your application has been submitted successfully" << endl;
                    }

                    flag = 0;
                    break;
                }
            }
        }
    }

    if (flag) {
        cout << "Wrong User name or Password" << endl;
    }

    file.close();
}
