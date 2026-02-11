GetSequence(const int& refId, const int& start, const int& stop, string& sequence) {


    if ( !IsOpen ) {
        cerr << "FASTA error : file not open for reading" << endl;
        return false;
    }


    if ( HasIndex && !Index.empty() ) {


        if ( (refId < 0) || (refId >= (int)Index.size()) ) {
            cerr << "FASTA error: invalid refId specified: " << refId << endl;
            return false;
        }


        const FastaIndexData& referenceData = Index.at(refId);


        if ( (start < 0) || (start > stop) || (stop > referenceData.Length) ) {
            cerr << "FASTA error: invalid start/stop positions specified: " << start << ", " << stop << endl;
            return false;
        }


        if ( fseeko(Stream, referenceData.Offset, SEEK_SET) != 0 ) {
            cerr << "FASTA error : could not sek in file" << endl;
            return false;
        }


        string fullSequence = "";
        if ( !GetNextSequence(fullSequence) ) {
            cerr << "FASTA error : could not retrieve sequence from FASTA file" << endl;
            return false;
        }


        const int seqLength = (stop - start) + 1;
        sequence = fullSequence.substr(start, seqLength);
        return true;
    }


    else {


        if ( !Rewind() ) {
            cerr << "FASTA error : could not rewind FASTA file" << endl;
            return false;
        }


        int currentId = 0;
        string header = "";
        string fullSequence = "";


        GetNextHeader(header);
        GetNextSequence(fullSequence);

        while ( currentId != refId ) {
            GetNextHeader(header);
            GetNextSequence(fullSequence);
            ++currentId;
        }


        if ( currentId == refId && (fullSequence.length() >= (size_t)stop) ) {
            const int seqLength = (stop - start) + 1;
            sequence = fullSequence.substr(start, seqLength);
            return true;
        }


        return false;
    }


    return true;
}
