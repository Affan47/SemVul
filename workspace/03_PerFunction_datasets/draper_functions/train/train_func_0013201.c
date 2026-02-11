Open(const string& filename, const string& indexFilename) {

    bool success = true;


    Stream = fopen(filename.c_str(), "rb");
    if ( !Stream ) {
        cerr << "FASTA error: Could not open " << filename << " for reading" << endl;
        return false;
    }
    IsOpen = true;
    success &= IsOpen;


    if ( !indexFilename.empty() ) {
        IndexStream = fopen(indexFilename.c_str(), "rb");
        if ( !IndexStream ) {
            cerr << "FASTA error : Could not open " << indexFilename << " for reading." << endl;
            return false;
        }
        IsIndexOpen = true;
        success &= IsIndexOpen;


        HasIndex = LoadIndexData();
        success &= HasIndex;
    }


    return success;
}
