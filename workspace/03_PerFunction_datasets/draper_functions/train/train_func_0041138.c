LocateIndex(const string& bamFilename,
                                            const BamIndex::IndexType& preferredType)
{

    const string& indexFilename = BamIndexFactory::FindIndexFilename(bamFilename, preferredType);


    if ( indexFilename.empty() )
        return false;


    return OpenIndex(indexFilename);
}
