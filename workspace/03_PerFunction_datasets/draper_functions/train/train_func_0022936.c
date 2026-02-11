flmNextKey(
	FDB *			pDb,
	LFILE *		pLFile,
	BTSK *		pStack,
	FLMUINT *	puiRefDrn)
{
	RCODE			rc;
	FLMBYTE *	pCurElm;


	pStack->uiFlags = NO_STACK;
	pStack->uiKeyBufSize = MAX_KEY_SIZ;

	pCurElm = CURRENT_ELM( pStack);


	while( BBE_NOT_LAST( pCurElm))
	{


		if( RC_BAD(rc = FSBtNextElm( pDb, pLFile, pStack)))
		{
			if( rc == FERR_BT_END_OF_DATA)
				rc = RC_SET( FERR_BTREE_ERROR);
			goto Exit;
		}
		pCurElm = CURRENT_ELM( pStack);
	}


	if( RC_BAD(rc = FSBtNextElm( pDb, pLFile, pStack)))
	{
		if( rc == FERR_BT_END_OF_DATA)
			rc = RC_SET( FERR_EOF_HIT);
		goto Exit;
	}
	if (puiRefDrn)
	{
		pCurElm = CURRENT_ELM( pStack);
		(void) FSGetDomain( &pCurElm, BBE_KEY);

		if( puiRefDrn)
		{
			*puiRefDrn = SENNextVal( &pCurElm);
		}
	}

Exit:
	return( rc);
}
