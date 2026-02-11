truncate(
	FLMUINT		uiTruncateSize)
{
	RCODE			rc = FERR_OK;
	FLMUINT		uiFileNum;

	flmAssert( uiTruncateSize >= 512);


	flmAssert( !m_pFile->ucLastCommittedLogHdr[LOG_KEEP_RFL_FILES]);


	flmAssert( !m_bLoggingUnknown);


	flmAssert( !m_uiCurrTransID);


	uiFileNum = (FLMUINT) FB2UD( &m_pFile->ucLastCommittedLogHdr[
																		LOG_RFL_FILE_NUM]);

	if (RC_BAD( rc = openFile( uiFileNum, &m_pFile->ucLastCommittedLogHdr[
					  LOG_LAST_TRANS_RFL_SERIAL_NUM])))
	{
		if (rc == FERR_IO_PATH_NOT_FOUND || rc == FERR_IO_INVALID_PATH)
		{
			rc = FERR_OK;
		}

		goto Exit;
	}

	if (RC_BAD( rc = m_pFileHdl->truncateFile( uiTruncateSize)))
	{
		m_bRflVolumeOk = FALSE;
		goto Exit;
	}

Exit:

	return (rc);
}
