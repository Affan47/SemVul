ScaLinkToFileLogList(
	SCACHE *		pSCache)
{
	FFILE *		pFile = pSCache->pFile;
	FLMUINT		uiPrevBlkAddress;

	flmAssert( pSCache->ui16Flags & CA_DIRTY);
	flmAssert( !(pSCache->ui16Flags & (CA_IN_FILE_LOG_LIST | CA_IN_NEW_LIST)));
	flmAssert( !pSCache->pPrevInReplaceList);
	flmAssert( !pSCache->pNextInReplaceList);

	uiPrevBlkAddress = scaGetPriorImageAddress( pSCache);
	if( (uiPrevBlkAddress && uiPrevBlkAddress != BT_END) ||
		!pSCache->pNextInVersionList)
	{
		goto Exit;
	}

	if( (pSCache->pNextInReplaceList = pFile->pFirstInLogList) != NULL)
	{
		pSCache->pNextInReplaceList->pPrevInReplaceList = pSCache;
	}
	else
	{
		pFile->pLastInLogList = pSCache;
	}

	scaSetFlags( pSCache, CA_IN_FILE_LOG_LIST);
	pSCache->pPrevInReplaceList = NULL;
	pFile->pFirstInLogList = pSCache;
	pFile->uiLogListCount++;

Exit:

	return;
}
