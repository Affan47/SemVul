FlushLRU()

{
    CPLAssert( poLRUStart != NULL );

    VSICacheChunk *poBlock = poLRUStart;

    CPLAssert( nCacheUsed >= poBlock->nDataFilled );

    nCacheUsed -= poBlock->nDataFilled;

    poLRUStart = poBlock->poLRUNext;
    if( poLRUEnd == poBlock )
        poLRUEnd = NULL;

    if( poBlock->poLRUNext != NULL )
        poBlock->poLRUNext->poLRUPrev = NULL;

    CPLAssert( !poBlock->bDirty );

    apoCache[poBlock->iBlock] = NULL;

    delete poBlock;
}
