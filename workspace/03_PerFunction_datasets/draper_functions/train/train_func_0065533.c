streamCopyLicense(istream& src, ostream& dst, const string& exceptiontag)
{
    string          s;
    vector<string>	H;


    while (getline(src,s) && isBlank(s)) dst << s << endl;


    if (s.find("/*")==string::npos) { dst << s << endl; return; }


    bool remove = false;
    H.push_back(s);

    while (getline(src,s) && s.find("*/")==string::npos) {
        H.push_back(s);
        if (s.find(exceptiontag) != string::npos) remove=true;
    }


    if (!remove) {

        for (unsigned int i=0; i<H.size(); i++) {
            dst << H[i] << endl;
        }
        dst << s << endl;
    }
}
