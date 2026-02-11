OpenDatabase(
	FLMUNICODE *		puzDbPath,
	FLMUNICODE *		puzDataDir,
	FLMUNICODE *		puzRflDir,
	FLMUINT				uiOpenFlags)
{
	RCODE			rc = FERR_OK;
	char *		pszDbPath = NULL;
	char *		pszDataDir;
	char *		pszRflDir;


	flmAssert( m_bSetupCalled == TRUE);
	flmAssert( m_hDb == HFDB_NULL);

	if (RC_BAD( rc = f_alloc( F_PATH_MAX_SIZE * 3, &pszDbPath)))
	{
		goto Exit;
	}

	pszDataDir = pszDbPath + F_PATH_MAX_SIZE;
	pszRflDir = pszDataDir + F_PATH_MAX_SIZE;


	if (!puzDbPath)
	{
		rc = RC_SET( FERR_MEM);
		goto Exit;
	}


	if (RC_BAD( rc = m_pServerContext->BuildFilePath( puzDbPath, pszDbPath)))
	{
		goto Exit;
	}


	if (puzDataDir)
	{
		if (RC_BAD( rc = m_pServerContext->BuildFilePath( puzDataDir, pszDataDir)))
		{
			goto Exit;
		}
	}
	else
	{
		pszDataDir = NULL;
	}


	if (puzRflDir)
	{
		if (RC_BAD( rc = m_pServerContext->BuildFilePath( puzRflDir, pszRflDir)))
		{
			goto Exit;
		}
	}
	else
	{
		*pszRflDir = 0;
	}


	if (RC_BAD( rc = FlmDbOpen( pszDbPath, pszDataDir, pszRflDir, uiOpenFlags,
				  NULL, &m_hDb)))
	{
		goto Exit;
	}

Exit:

	if (pszDbPath)
	{
		f_free( &pszDbPath);
	}


	if (RC_BAD( rc))
	{
		if (m_hDb != HFDB_NULL)
		{
			(void) FlmDbClose( &m_hDb);
		}
	}

	return (rc);
}
