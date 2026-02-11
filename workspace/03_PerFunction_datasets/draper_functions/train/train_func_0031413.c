ScaLinkToFreeList(
	SCACHE *		pSCache,
	FLMUINT		uiFreeTime)
{
	flmAssert( !pSCache->ui16Flags);
	flmAssert( !pSCache->pFile);
	flmAssert( !pSCache->pPrevInReplaceList);
	flmAssert( !pSCache->pNextInReplaceList);

	if( pSCache->uiHighTransID != 0xFFFFFFFF)
	{


		scaSetTransID( pSCache, 0xFFFFFFFF);
	}

	if( (pSCache->pNextInFile = gv_FlmSysData.SCacheMgr.pFirstFree) != NULL)
	{
		pSCache->pNextInFile->pPrevInFile = pSCache;
	}
	else
	{
		gv_FlmSysData.SCacheMgr.pLastFree = pSCache;
	}

	pSCache->pPrevInFile = NULL;
	pSCache->uiBlkAddress = uiFreeTime;
	pSCache->ui16Flags = CA_FREE;
	gv_FlmSysData.SCacheMgr.pFirstFree = pSCache;
	gv_FlmSysData.SCacheMgr.uiFreeBytes += SCA_MEM_SIZE( pSCache);
	gv_FlmSysData.SCacheMgr.uiFreeCount++;
}
