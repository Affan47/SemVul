SyHashInsert(SyHash *pHash, const void *pKey, sxu32 nKeyLen, void *pUserData)
{
	SyHashEntry_Pr *pEntry;
	sxi32 rc;
#if defined(UNTRUST)
	if( INVALID_HASH(pHash) || pKey == 0 ){
		return SXERR_CORRUPT;
	}
#endif
	if( pHash->nEntry >= pHash->nBucketSize * SXHASH_FILL_FACTOR ){
		rc = HashGrowTable(&(*pHash));
		if( rc != SXRET_OK ){
			return rc;
		}
	}

	pEntry = (SyHashEntry_Pr *)SyMemBackendPoolAlloc(pHash->pAllocator, sizeof(SyHashEntry_Pr));
	if( pEntry == 0 ){
		return SXERR_MEM;
	}

	SyZero(pEntry, sizeof(SyHashEntry_Pr));
	pEntry->pHash = pHash;
	pEntry->pKey = pKey;
	pEntry->nKeyLen = nKeyLen;
	pEntry->pUserData = pUserData;
	pEntry->nHash = pHash->xHash(pEntry->pKey, pEntry->nKeyLen);

	rc = HashInsert(&(*pHash), pEntry);
	return rc;
}
