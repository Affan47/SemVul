getFullRflFileName(
	FLMUINT	uiFileNum,
	char *	pszRflFileName)
{
	RCODE 	rc = FERR_OK;
	char		szBaseName[F_FILENAME_SIZE];


	f_strcpy( pszRflFileName, m_szRflDir);


	getBaseRflFileName( uiFileNum, szBaseName);


	if (RC_BAD( rc = gv_FlmSysData.pFileSystem->pathAppend(
		pszRflFileName, szBaseName)))
	{
		goto Exit;
	}

Exit:

	return (rc);
}
