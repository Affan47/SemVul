UpdateCache(void) {


    if ( !IsOpen() ) return;


    switch ( m_cacheMode ) {

        case (BamIndex::FullIndexCaching) :
            Rewind();
            LoadAllReferences(true);
            break;

        case (BamIndex::LimitedIndexCaching) :
            if ( HasFullDataCache() )
                KeepOnlyFirstReferenceOffsets();
            else {
                ClearAllData();
                SkipToFirstReference();
                LoadFirstReference(true);
            }
            break;

        case(BamIndex::NoIndexCaching) :
            ClearAllData();
            break;

        default :

            ;
    }
}
