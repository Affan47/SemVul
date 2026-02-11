HandleManager_addHandle( HandleManager *pHm, u32 pData ) {
    int handle = -1;

    if( pHm ) {
        if( pHm->mFirstFreeIndex < 0 )
            Resize( pHm );

        handle = pHm->mFirstFreeIndex;

        pHm->mHandles[handle].handle = pData;
        pHm->mHandles[handle].used = true;
        pHm->mFirstFreeIndex = pHm->mHandles[handle].next_free_index;

        ++pHm->mCount;
        ++pHm->mMaxIndex;
    }

    return handle;
}
