flmRcaUnlinkFromHashBucket(
	RCACHE *			pRCache)
{
	flmAssert( pRCache->pNewerVersion == NULL);
	if (pRCache->pNextInBucket)
	{
		pRCache->pNextInBucket->pPrevInBucket = pRCache->pPrevInBucket;
	}

	if (pRCache->pPrevInBucket)
	{
		pRCache->pPrevInBucket->pNextInBucket = pRCache->pNextInBucket;
	}
	else
	{
		RCACHE ** ppHashBucket = FLM_RCA_HASH( pRCache->uiDrn);
		*ppHashBucket = pRCache->pNextInBucket;
	}
	pRCache->pPrevInBucket = pRCache->pNextInBucket = NULL;
}
