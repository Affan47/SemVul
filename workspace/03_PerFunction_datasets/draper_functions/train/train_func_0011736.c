GenerateSortedRuns(void) {


    BamReader inputReader;
    if ( !inputReader.Open(m_settings->InputBamFilename) ) {
        cerr << "bamtools sort ERROR: could not open " << m_settings->InputBamFilename
             << " for reading... Aborting." << endl;
        return false;
    }


    SamHeader header = inputReader.GetHeader();
    header.SortOrder = m_sort.getSamHeaderSort();
    m_headerText = header.ToString();
    m_references = inputReader.GetReferenceData();


    BamAlignment al;
    vector<BamAlignment> buffer;
    buffer.reserve(m_settings->MaxBufferCount);


    if (!m_sort.isTagCoreAttribute() ) {


        while ( inputReader.GetNextAlignment(al)) {


            buffer.push_back(al);


            if ( buffer.size() == m_settings->MaxBufferCount )
                HandleBufferContents(buffer);
        }

    }


    else {


        while ( inputReader.GetNextAlignmentCore(al) ) {


            buffer.push_back(al);


            if ( buffer.size() == m_settings->MaxBufferCount ){
                HandleBufferContents(buffer);
            }
        }
    }


    if ( buffer.size() > 0 )
        HandleBufferContents(buffer);


    inputReader.Close();
    return true;
}
