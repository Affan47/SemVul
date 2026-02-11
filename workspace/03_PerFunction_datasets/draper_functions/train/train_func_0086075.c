retrieveRecord(
	F_Session *	pFlmSession,
	HFDB				hDb,
	const char *	pszDbKey,
	FLMUINT			uiDrn,
	FLMUINT			uiContainer,
	FLMBOOL			bReadOnly,
	FLMUINT			uiFlag)
{
	RCODE				rc = FERR_OK;
	FlmRecord *		pRec = NULL;
	char				szTmp[ 20];
	char *			pTmp = &szTmp[ 0];
	FLMUINT			uiFlags = FO_EXACT;

	if (uiFlag == 0xFFFFFFFF)
	{

		if (RC_OK( rc = getFormValueByName( "flags", &pTmp, sizeof( szTmp), NULL)))
		{
			uiFlags = f_atoud( szTmp);
		}
	}
	else
	{
		uiFlags = uiFlag;
	}

	rc = FlmRecordRetrieve( hDb, uiContainer, uiDrn, uiFlags, (FlmRecord **)&pRec, &uiDrn);
	if ((rc == FERR_NOT_FOUND) && (uiDrn == 0))
	{
		rc = FERR_OK;
	}

	displayRecordPage( pFlmSession, hDb, pszDbKey, pRec, bReadOnly, rc);

	if (pRec)
	{
		pRec->Release();
	}

	return;
}
