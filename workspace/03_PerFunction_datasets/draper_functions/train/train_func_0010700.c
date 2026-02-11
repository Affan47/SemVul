MemHashGetEntry(
	mem_hash_kv_engine *pEngine,
	const void *pKey,int nKeyLen
	)
{
	mem_hash_record *pEntry;
	sxu32 nHash,nBucket;

	nHash = pEngine->xHash(pKey,(sxu32)nKeyLen);
	nBucket = nHash & (pEngine->nBucket - 1);
	pEntry = pEngine->apBucket[nBucket];
	for(;;){
		if( pEntry == 0 ){
			break;
		}
		if( pEntry->nHash == nHash && pEntry->nKeyLen == (sxu32)nKeyLen &&
			pEngine->xCmp(pEntry->pKey,pKey,pEntry->nKeyLen) == 0 ){
				return pEntry;
		}
		pEntry = pEntry->pNextHash;
	}

	return 0;
}
