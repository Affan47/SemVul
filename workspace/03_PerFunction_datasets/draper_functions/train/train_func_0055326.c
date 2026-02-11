DeAllocBCN( BCN *pBCN )
{
    int    i, k;
    FTCN  *ftcn;
    if ( !pBCN )
        return;
    if ( pBCN->pRankStack ) {
        for ( i = 0; i < pBCN->nMaxLenRankStack; i ++ ) {
            FREE_ARRAY( pBCN->pRankStack[i] )
        }
        FREE_ARRAY( pBCN->pRankStack )
    }
    for ( k = 0; k < TAUT_NUM; k ++ ) {
        ftcn = pBCN->ftcn + k;
        FreeNeighList( ftcn->NeighList );
        FREE_ARRAY( ftcn->LinearCt )
        PartitionFree( &ftcn->PartitionCt );
        FREE_ARRAY( ftcn->nSymmRankCt )
        FREE_ARRAY( ftcn->nNumHOrig )
        FREE_ARRAY( ftcn->nNumH )
        FREE_ARRAY( ftcn->nNumHOrigFixH )
        FREE_ARRAY( ftcn->nNumHFixH )
        PartitionFree( &ftcn->PartitionCtIso );
        FREE_ARRAY( ftcn->nSymmRankCtIso )
        FREE_ARRAY( ftcn->iso_sort_keys )
        FREE_ARRAY( ftcn->iso_sort_keysOrig )
        FREE_ARRAY( ftcn->iso_exchg_atnos )
        FREE_ARRAY( ftcn->iso_exchg_atnosOrig )
    }
}
