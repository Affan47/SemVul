ScaUnlinkFromTransLogList(
	SCACHE *			pSCache,
	FFILE *			pFile)
{

#ifdef SCACHE_LINK_CHECKING


	{
		SCACHE **	ppSCacheBucket;
		SCACHE *		pTmpSCache;

		ppSCacheBucket = ScaHash(
					pFile->FileHdr.uiSigBitsInBlkSize,
					pSCache->uiBlkAddress);
		pTmpSCache = *ppSCacheBucket;
		while (pTmpSCache && pTmpSCache != pSCache)
			pTmpSCache = pTmpSCache->pNextInHashBucket;
		if (pTmpSCache)
		{
			f_breakpoint( 1001);
		}


		pTmpSCache = pFile->pTransLogList;
		while (pTmpSCache && pTmpSCache != pSCache)
			pTmpSCache = pTmpSCache->pNextInHashBucket;
		if (!pTmpSCache)
		{
			f_breakpoint(1002);
		}
	}
#endif

	if (pSCache->pPrevInHashBucket)
	{
		pSCache->pPrevInHashBucket->pNextInHashBucket = pSCache->pNextInHashBucket;
	}
	else
	{
		pFile->pTransLogList = pSCache->pNextInHashBucket;
	}

	if (pSCache->pNextInHashBucket)
	{
		pSCache->pNextInHashBucket->pPrevInHashBucket = pSCache->pPrevInHashBucket;
	}

	pSCache->pNextInHashBucket =
	pSCache->pPrevInHashBucket = NULL;
}
