GetHeaderText(void) const {


    if ( m_readers.size() == 1 ) {


        const ReaderAlignment& ra = m_readers.front();
        const BamReader* reader = ra.first;
        if ( reader ) return reader->GetHeaderText();


        return string();
    }

    string mergedHeader("");
    map<string, bool> readGroups;


    vector<ReaderAlignment>::const_iterator readerBegin = m_readers.begin();
    vector<ReaderAlignment>::const_iterator readerIter  = readerBegin;
    vector<ReaderAlignment>::const_iterator readerEnd   = m_readers.end();
    for ( ; readerIter != readerEnd; ++readerIter ) {
        const BamReader* reader = (*readerIter).first;
        if ( reader == 0 ) continue;


        string headerText = reader->GetHeaderText();
        if ( headerText.empty() ) continue;


        map<string, bool> currentFileReadGroups;
        const vector<string> lines = SplitHeaderText(headerText);


        vector<string>::const_iterator linesIter = lines.begin();
        vector<string>::const_iterator linesEnd  = lines.end();
        for ( ; linesIter != linesEnd; ++linesIter ) {


            const string headerLine = (*linesIter);
            if ( headerLine.empty() ) continue;


            if ( readerIter == readerBegin ) {
                if ( headerLine.find("@HD") == 0 || headerLine.find("@SQ") == 0) {
                    mergedHeader.append(headerLine.c_str());
                    mergedHeader.append(1, '\n');
                }
            }


            if ( headerLine.find("@RG") == 0 ) {


                const string readGroup = ExtractReadGroup(headerLine);


                if ( readGroups.find(readGroup) == readGroups.end() ) {
                    mergedHeader.append(headerLine.c_str() );
                    mergedHeader.append(1, '\n');
                    readGroups[readGroup] = true;
                    currentFileReadGroups[readGroup] = true;
                } else {


                    if ( currentFileReadGroups.find(readGroup) != currentFileReadGroups.end() ) {
                        cerr << "BamMultiReader WARNING: duplicate @RG tag " << readGroup
                             << " entry in header of " << reader->GetFilename() << endl;
                    }
                }
            }
        }
    }


    return mergedHeader;
}
