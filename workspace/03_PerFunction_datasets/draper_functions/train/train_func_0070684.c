internalGetSerializedNX(int32_t options, int32_t nxIndex, UErrorCode &errorCode) {

    UBool isCached;

    UMTX_CHECK(NULL, (UBool)(nxCache[options]!=NULL), isCached);

    if( !isCached &&
        canonStartSets!=NULL &&
        canonStartSets[nxIndex]!=0 && canonStartSets[nxIndex+1]>canonStartSets[nxIndex]
    ) {
        USerializedSet sset;
        UnicodeSet *set;
        UChar32 start, end;
        int32_t i;

        if( !uset_getSerializedSet(
                    &sset,
                    canonStartSets+canonStartSets[nxIndex],
                    canonStartSets[nxIndex+1]-canonStartSets[nxIndex])
        ) {
            errorCode=U_INVALID_FORMAT_ERROR;
            return NULL;
        }


        set=new UnicodeSet();
        if(set==NULL) {
            errorCode=U_MEMORY_ALLOCATION_ERROR;
            return NULL;
        }
        for(i=0; uset_getSerializedRange(&sset, i, &start, &end); ++i) {
            set->add(start, end);
        }

        set->compact();

        umtx_lock(NULL);
        if(nxCache[options]==NULL) {
            nxCache[options]=set;
            set=NULL;
            ucln_common_registerCleanup(UCLN_COMMON_UNORM, unorm_cleanup);
        }
        umtx_unlock(NULL);

        delete set;
    }

    return nxCache[options];
}
