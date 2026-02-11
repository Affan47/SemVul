SendFiletoTNC(const string& szName)
{
    int nTokens;
    char Line[256];
    const int maxToken = 15;

    timespec ts;
    ts.tv_sec = 0;

    ifstream file(szName.c_str());
    if (file.is_open () == false) {
        cerr << "Can't open " << szName << endl << flush;
        return -1;
    }

    Line[0] = 0x03;
    Line[1] = '\0';
    rfWrite(Line);
    ts.tv_sec = 1;
    ts.tv_nsec = 0;
    nanosleep(&ts,NULL);

    ts.tv_sec = 0;
    ts.tv_nsec = 500000000;

    while (file.good ()) {
        file.getline (Line, 256);
        strcat (Line, "\r");

        if ((Line[0] != '*') && (Line[0] != '#') && (strlen (Line) >= 2)) {
            string sLine(Line);
            string token[maxToken];
            nTokens = split(sLine, token, maxToken, RXwhite);
            upcase(token[0]);
            upcase(token[1]);

            if (token[0].compare("MYCALL") == 0) {
                MyCall = strdup(token[1].c_str());
                if (MyCall.length() > 9) {
                    string tmpstr;
                    tmpstr = MyCall.substr(0,9);

                    MyCall = tmpstr;
                }
            }

            if ((token[0].compare("UNPROTO") == 0) && (nTokens >= 2)) {
                size_t idx2 = sLine.find(token[1],6);
                sLine.replace(idx2, token[1].length(), PGVERS);
            }

            cout << sLine.c_str() << endl;
            int len = sLine.length();

            write (ttySwrite, Line, len);
            nanosleep(&ts,NULL);
        }
    }
    file.close ();
    return 0;
}
