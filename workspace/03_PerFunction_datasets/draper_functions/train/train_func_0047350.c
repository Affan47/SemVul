FlmDbCopy(
	const char *		pszSrcDbName,
	const char *		pszSrcDataDir,
	const char *		pszSrcRflDir,
	const char *		pszDestDbName,
	const char *		pszDestDataDir,
	const char *		pszDestRflDir,
	STATUS_HOOK			fnStatusCallback,
	void *				UserData)
{
	RCODE				rc = FERR_OK;
	FLMBYTE *		pucLastCommittedLogHdr;
	HFDB				hDb = HFDB_NULL;
	FDB *				pDb;
	FLMBOOL			bDbLocked = FALSE;
	FLMUINT			uiDbVersion;


	if (RC_BAD( rc = FlmConfig( FLM_CLOSE_FILE,
		(void *)pszDestDbName, (void *)pszDestDataDir)))
	{
		goto Exit;
	}

	gv_FlmSysData.pFileHdlCache->closeUnusedFiles();


	if (RC_BAD( rc = FlmDbOpen( pszSrcDbName, pszSrcDataDir, pszSrcRflDir,
								0, NULL, &hDb)))
	{
		goto Exit;
	}
	pDb = (FDB *)hDb;


	if (RC_BAD( rc = FlmDbLock( hDb, FLM_LOCK_EXCLUSIVE, 0, FLM_NO_TIMEOUT)))
	{
		goto Exit;
	}
	bDbLocked = TRUE;


	if (RC_BAD( rc = FlmDbCheckpoint( hDb, FLM_NO_TIMEOUT)))
	{
		goto Exit;
	}

	pucLastCommittedLogHdr = &pDb->pFile->ucLastCommittedLogHdr[ 0];


	uiDbVersion = pDb->pFile->FileHdr.uiVersionNum;


	rc = flmCopyDb( uiDbVersion, pszSrcDbName, pszSrcDataDir, pszSrcRflDir,
						pszDestDbName, pszDestDataDir, pszDestRflDir,
						fnStatusCallback, UserData);

Exit:


	if (bDbLocked)
	{
		FlmDbUnlock( hDb);
	}

	if (hDb != HFDB_NULL)
	{
		(void)FlmDbClose( &hDb);
		(void)FlmConfig( FLM_CLOSE_FILE, (void *)pszSrcDbName,
								(void *)pszSrcDataDir);
	}
	return( rc);
}
