TransformEx( int nCount,
                             double *x, double *y, double *z = NULL,
                             int *pabSuccess = NULL )
    {
        int nResult = TRUE;
        if( poCT1 )
            nResult = poCT1->TransformEx(nCount, x, y, z, pabSuccess);
        if( nResult && poCT2 )
            nResult = poCT2->TransformEx(nCount, x, y, z, pabSuccess);
        return nResult;
    }
