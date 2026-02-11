GetFeature( long nFID )
{
    if (nFID < 0 || nFID >= nRecords)
        return NULL;

    nNextFID = nFID;
    VSIFSeekL( fpPDS, nStartBytes + nNextFID * nRecordSize, SEEK_SET );
    return GetNextRawFeature();
}
