MemBackendPoolAlloc(SyMemBackend *pBackend, sxu32 nByte)
{
	SyMemHeader *pBucket, *pNext;
	sxu32 nBucketSize;
	sxu32 nBucket;

	if( nByte + sizeof(SyMemHeader) >= SXMEM_POOL_MAXALLOC ){

		pBucket = (SyMemHeader *)MemBackendAlloc(&(*pBackend), nByte+sizeof(SyMemHeader));
		if( pBucket == 0 ){
			return 0;
		}

		pBucket->nBucket = (sxu32)(SXMEM_POOL_MAGIC << 16) | SXU16_HIGH;
		return (void *)(pBucket+1);
	}

	nBucket = 0;
	nBucketSize = SXMEM_POOL_MINALLOC;
	while( nByte + sizeof(SyMemHeader) > nBucketSize  ){
		nBucketSize <<= 1;
		nBucket++;
	}
	pBucket = pBackend->apPool[nBucket];
	if( pBucket == 0 ){
		sxi32 rc;
		rc = MemPoolBucketAlloc(&(*pBackend), nBucket);
		if( rc != SXRET_OK ){
			return 0;
		}
		pBucket = pBackend->apPool[nBucket];
	}

	pNext = pBucket->pNext;
	pBackend->apPool[nBucket] = pNext;

	pBucket->nBucket = (SXMEM_POOL_MAGIC << 16) | nBucket;
	return (void *)&pBucket[1];
}
