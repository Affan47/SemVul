GetByIndex( int nIndex )

{
    if( !bSorted )
        Sort();

    if( nIndex < 0 || nIndex >= nRecordCount )
        return NULL;
    else
        return pasRecords[nIndex].poRecord;
}
