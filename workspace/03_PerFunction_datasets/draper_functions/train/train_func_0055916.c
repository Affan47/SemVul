flmReadFileHdr(
	const char *		pszDbPath,
	DB_STATS *			pDbStats,
	FFILE *				pFile,
	LOG_HDR *			pLogHdr,
	FLMBOOL				bAllowLimitedMode)
{
	RCODE					rc = FERR_OK;
	IF_FileHdl *		pFileHdl = NULL;


	if( RC_BAD( rc = gv_FlmSysData.pFileSystem->openFile( pszDbPath,
		gv_FlmSysData.uiFileOpenFlags, &pFileHdl)))
	{
		goto Exit;
	}

	if (RC_BAD( rc = flmReadAndVerifyHdrInfo( pDbStats,
		pFileHdl, pFile->pucLogHdrIOBuf,
		&pFile->FileHdr, pLogHdr, NULL)))
	{
		goto Exit;
	}


	f_memcpy( pFile->ucLastCommittedLogHdr,
			&pFile->pucLogHdrIOBuf[ DB_LOG_HEADER_START], LOG_HEADER_SIZE);


#ifdef FLM_USE_NICI
	if( pFile->FileHdr.uiVersionNum >= FLM_FILE_FORMAT_VER_4_60)
	{
		FLMUINT32	ui32KeyLen;

		ui32KeyLen = FB2UW( &pFile->ucLastCommittedLogHdr[ LOG_DATABASE_KEY_LEN]);


		if (ui32KeyLen == 0)
		{
			pFile->rcLimitedCode = FERR_ENCRYPTION_UNAVAILABLE;
			pFile->bInLimitedMode = TRUE;
			pFile->bHaveEncKey = FALSE;
		}
		else
		{


			pFile->bHaveEncKey = TRUE;

			if ((pFile->pDbWrappingKey = f_new F_CCS) == NULL)
			{
				rc = RC_SET( FERR_MEM);
				goto Exit;
			}

			if( RC_BAD( rc = pFile->pDbWrappingKey->init( TRUE, FLM_NICI_AES)))
			{
				goto Exit;
			}


			if( RC_BAD( rc = pFile->pDbWrappingKey->setKeyFromStore(
									&pFile->ucLastCommittedLogHdr[LOG_DATABASE_KEY],
									ui32KeyLen, pFile->pszDbPassword, NULL, FALSE)))
			{
				if (bAllowLimitedMode)
				{
					pFile->rcLimitedCode = rc;
					rc = FERR_OK;
					pFile->bInLimitedMode = TRUE;
				}
				else
				{
					goto Exit;
				}
			}
		}
	}
	else
	{
		pFile->rcLimitedCode = FERR_ENCRYPTION_UNAVAILABLE;
		pFile->bInLimitedMode = TRUE;
		pFile->bHaveEncKey = FALSE;
	}
#else
	F_UNREFERENCED_PARM( bAllowLimitedMode);
	pFile->rcLimitedCode = FERR_ENCRYPTION_UNAVAILABLE;
	pFile->bInLimitedMode = TRUE;
	pFile->bHaveEncKey = FALSE;
#endif


	pFile->uiMaxFileSize = flmGetMaxFileSize(
									pFile->FileHdr.uiVersionNum,
									pFile->ucLastCommittedLogHdr);
Exit:

	if( pFileHdl)
	{
		pFileHdl->Release();
	}

	return( rc);
}
