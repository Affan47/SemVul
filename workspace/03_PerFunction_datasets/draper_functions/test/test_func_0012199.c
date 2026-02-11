SortIndexSection( OGRField *pasIndexFields,
                                              int nStart, int nEntries )

{
    if( nEntries < 2 )
        return;

    swq_select *psSelectInfo = (swq_select *) pSelectInfo;
    int      nOrderItems = psSelectInfo->order_specs;

    int nFirstGroup = nEntries / 2;
    int nFirstStart = nStart;
    int nSecondGroup = nEntries - nFirstGroup;
    int nSecondStart = nStart + nFirstGroup;
    int iMerge = 0;
    long *panMerged;

    SortIndexSection( pasIndexFields, nFirstStart, nFirstGroup );
    SortIndexSection( pasIndexFields, nSecondStart, nSecondGroup );

    panMerged = (long *) CPLMalloc( sizeof(long) * nEntries );

    while( iMerge < nEntries )
    {
        int  nResult;

        if( nFirstGroup == 0 )
            nResult = -1;
        else if( nSecondGroup == 0 )
            nResult = 1;
        else
            nResult = Compare( pasIndexFields
                               + panFIDIndex[nFirstStart] * nOrderItems,
                               pasIndexFields
                               + panFIDIndex[nSecondStart] * nOrderItems );

        if( nResult < 0 )
        {
            panMerged[iMerge++] = panFIDIndex[nSecondStart++];
            nSecondGroup--;
        }
        else
        {
            panMerged[iMerge++] = panFIDIndex[nFirstStart++];
            nFirstGroup--;
        }
    }


    memcpy( panFIDIndex + nStart, panMerged, sizeof(long) * nEntries );
    CPLFree( panMerged );
}
