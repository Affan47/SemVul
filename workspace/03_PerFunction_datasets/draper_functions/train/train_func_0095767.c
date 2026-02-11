MakeData( int nSize )

{
    if( poType == NULL )
    {
        poType = psHFA->poDictionary->FindType( szType );
        if( poType == NULL )
            return NULL;
    }

    if( nSize == 0 && poType->nBytes > 0 )
        nSize = poType->nBytes;

    if( (int) nDataSize < nSize && nSize > 0 )
    {
        pabyData = (GByte *) CPLRealloc(pabyData, nSize);
        memset( pabyData + nDataSize, 0, nSize - nDataSize );
        nDataSize = nSize;

        MarkDirty();


        if( nFilePos != 0 )
        {
            nFilePos = 0;
            nDataPos = 0;
            if (poPrev != NULL) poPrev->MarkDirty();
            if (poNext != NULL) poNext->MarkDirty();
            if (poChild != NULL) poChild->MarkDirty();
            if (poParent != NULL) poParent->MarkDirty();
        }
    }
    else
        LoadData();

    return pabyData;
}
