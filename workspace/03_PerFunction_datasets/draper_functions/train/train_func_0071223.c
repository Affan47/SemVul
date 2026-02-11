parseQuery(
	HFDB				hDb,
	FLMUINT			uiContainer,
	FLMUINT			uiIndex,
	F_NameTable *	pNameTable,
	const char *	pszQueryCriteria,
	HFCURSOR *		phCursor)
{
	RCODE				rc = FERR_OK;

	*phCursor = HFCURSOR_NULL;
	if (RC_BAD( rc = FlmCursorInit( hDb, uiContainer, phCursor)))
	{
		goto Exit;
	}
	if (RC_BAD( rc = FlmCursorConfig( *phCursor, FCURSOR_SET_FLM_IX,
						(void *)uiIndex, 0)))
	{
		goto Exit;
	}
	if (RC_BAD( rc = FlmParseQuery( *phCursor, pNameTable, pszQueryCriteria)))
	{
		goto Exit;
	}


	if (RC_BAD( rc = FlmCursorValidate( *phCursor)))
	{
		goto Exit;
	}

Exit:

	if (RC_BAD( rc) && *phCursor != HFCURSOR_NULL)
	{
		FlmCursorFree( phCursor);
	}

	return( rc);
}
