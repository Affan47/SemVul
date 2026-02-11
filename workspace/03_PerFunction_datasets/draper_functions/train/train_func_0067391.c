ParseSamLine(const string& line) {


    if (line.length() < 5 ) return;


    const string firstToken = line.substr(0,3);
    string restOfLine = line.substr(4);
    if      ( firstToken == Constants::SAM_HD_BEGIN_TOKEN) ParseHDLine(restOfLine);
    else if ( firstToken == Constants::SAM_SQ_BEGIN_TOKEN) ParseSQLine(restOfLine);
    else if ( firstToken == Constants::SAM_RG_BEGIN_TOKEN) ParseRGLine(restOfLine);
    else if ( firstToken == Constants::SAM_PG_BEGIN_TOKEN) ParsePGLine(restOfLine);
    else if ( firstToken == Constants::SAM_CO_BEGIN_TOKEN) ParseCOLine(restOfLine);
    else
        cerr << "SamFormatParser ERROR: unknown token: " << firstToken << endl;

    return;
}
