CreateIndex(BamReaderPrivate* reader,
                                            const BamIndex::IndexType& type) {


    if ( reader == 0 )
        return false;


    BamIndex* newIndex = BamIndexFactory::CreateIndexOfType(type);
    if ( newIndex == 0 ) {
        cerr << "BamRandomAccessController ERROR: could not create index of type " << type << endl;
        return false;
    }


    if ( !newIndex->Build(reader) ) {
        cerr << "BamRandomAccessController ERROR: could not build index on BAM file: " << reader->Filename() << endl;
        return false;
    }


    SetIndex(newIndex);


    if ( newIndex->Write(reader->Filename()) ) {
        cerr << "BamRandomAccessController ERROR: could not save new index for BAM file: " << reader->Filename() << endl;
        return false;
    }


    newIndex->SetCacheMode(m_indexCacheMode);
    return true;
}
