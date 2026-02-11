MemHashUnlinkRecord(mem_hash_kv_engine *pEngine,mem_hash_record *pEntry)
{
	sxu32 nBucket = pEntry->nHash & (pEngine->nBucket - 1);
	SyMemBackend *pAlloc = &pEngine->sAlloc;
	if( pEntry->pPrevHash == 0 ){
		pEngine->apBucket[nBucket] = pEntry->pNextHash;
	}else{
		pEntry->pPrevHash->pNextHash = pEntry->pNextHash;
	}
	if( pEntry->pNextHash ){
		pEntry->pNextHash->pPrevHash = pEntry->pPrevHash;
	}
	MACRO_LD_REMOVE(pEngine->pLast,pEntry);
	if( pEntry == pEngine->pFirst ){
		pEngine->pFirst = pEntry->pPrev;
	}
	pEngine->nRecord--;

	SyMemBackendFree(pAlloc,(void *)pEntry->pData);
	SyMemBackendFree(pAlloc,pEntry);
}
