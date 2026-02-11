setup(
	FLMUINT				uiMTUSize,
	F_Restore *			pRestoreObj)
{
	RCODE			rc = FERR_OK;

	flmAssert( pRestoreObj);
	flmAssert( !m_bSetup);

	m_pRestoreObj = pRestoreObj;
	m_uiMTUSize = uiMTUSize;

	if( RC_BAD( rc = _setup()))
	{
		goto Exit;
	}


	if( RC_BAD( rc = startThreads()))
	{
		goto Exit;
	}

	m_bSetup = TRUE;

Exit:

	return( rc);
}
