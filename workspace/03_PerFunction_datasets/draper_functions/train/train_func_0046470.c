ScaStepUpInReplaceList(
	SCACHE *		pSCache)
{
	SCACHE *		pPrevSCache;

	flmAssert( !pSCache->ui16Flags);

	if( (pPrevSCache = pSCache->pPrevInReplaceList) != NULL)
	{
		if( pPrevSCache->pPrevInReplaceList)
		{
			pPrevSCache->pPrevInReplaceList->pNextInReplaceList = pSCache;
		}
		else
		{
			gv_FlmSysData.SCacheMgr.pMRUReplace = pSCache;
		}

		pSCache->pPrevInReplaceList = pPrevSCache->pPrevInReplaceList;
		pPrevSCache->pPrevInReplaceList = pSCache;
		pPrevSCache->pNextInReplaceList = pSCache->pNextInReplaceList;

		if( pSCache->pNextInReplaceList)
		{
			pSCache->pNextInReplaceList->pPrevInReplaceList = pPrevSCache;
		}
		else
		{
			gv_FlmSysData.SCacheMgr.pLRUReplace = pPrevSCache;
		}
		pSCache->pNextInReplaceList = pPrevSCache;
	}
}
