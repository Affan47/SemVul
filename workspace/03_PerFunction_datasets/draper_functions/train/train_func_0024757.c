flmLFileRead(
	FDB *			pDb,
	LFILE *		pLFile)
{
	RCODE			rc = FERR_OK;
	SCACHE *		pSCache;
	FLMBOOL		bReleaseCache = FALSE;


	if (RC_BAD( rc = ScaGetBlock( pDb, NULL, BHT_LFH_BLK,
								pLFile->uiBlkAddress, NULL, &pSCache)))
	{
		goto Exit;
	}
	bReleaseCache = TRUE;


	if( RC_BAD( rc = flmBufferToLFile(
		&pSCache->pucBlk[ pLFile->uiOffsetInBlk],
		pLFile, pLFile->uiBlkAddress, pLFile->uiOffsetInBlk)))
	{
		goto Exit;
	}

Exit:

	if (bReleaseCache)
	{
		ScaReleaseCache( pSCache, FALSE);
	}

	return( rc);
}
