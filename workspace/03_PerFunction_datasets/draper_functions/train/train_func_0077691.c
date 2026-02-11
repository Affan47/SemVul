FindIndexFilename(const string& bamFilename,
                                                const BamIndex::IndexType& preferredType)
{


    string indexFilename = CreateIndexFilename(bamFilename, preferredType);
    if ( !indexFilename.empty() && BamTools::FileExists(indexFilename) )
        return indexFilename;


    if ( preferredType != BamIndex::STANDARD ) {
        indexFilename = CreateIndexFilename(bamFilename, BamIndex::STANDARD);
        if ( !indexFilename.empty() && BamTools::FileExists(indexFilename) )
            return indexFilename;
    }
    if ( preferredType != BamIndex::BAMTOOLS ) {
        indexFilename = CreateIndexFilename(bamFilename, BamIndex::BAMTOOLS);
        if ( !indexFilename.empty() && BamTools::FileExists(indexFilename) )
            return indexFilename;
    }


    return string();
}
