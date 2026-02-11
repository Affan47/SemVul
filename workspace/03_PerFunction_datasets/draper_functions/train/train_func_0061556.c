BuildFilePath(
	const FLMUNICODE *		puzUrlString,
	char *						pszFilePathRV)
{
	RCODE				rc = FERR_OK;
	char				szBasePath[F_PATH_MAX_SIZE];
	FUrl				Url;
	char *			pucAsciiUrl;
	const char *	pszFile;
	F_Pool			tmpPool;


	tmpPool.poolInit( 256);


	if (RC_BAD( rc = fcsConvertUnicodeToNative( &tmpPool, puzUrlString,
				  &pucAsciiUrl)))
	{
		goto Exit;
	}


	if (RC_BAD( rc = Url.SetUrl( pucAsciiUrl)))
	{
		goto Exit;
	}

	pszFile = Url.GetFile();

	if (Url.GetRelative())
	{


		GetBasePath( szBasePath);


		f_strcpy( pszFilePathRV, szBasePath);
		if (RC_BAD( rc = gv_FlmSysData.pFileSystem->pathAppend(
			pszFilePathRV, pszFile)))
		{
			goto Exit;
		}
	}
	else
	{


		f_strcpy( pszFilePathRV, pszFile);
	}

Exit:

	return (rc);
}
