flmCurPositionable(
	CURSOR *		pCursor,
	FLMBOOL *	pbPositionable)
{
	RCODE			rc = FERR_OK;
	SUBQUERY *	pSubQuery;

	*pbPositionable = FALSE;


	if (!pCursor->bOptimized)
	{
		if( RC_BAD( rc = flmCurPrep( pCursor)))
		{
			goto Exit;
		}
	}


	if (((pSubQuery = pCursor->pSubQueryList) != NULL) &&
		 (!pSubQuery->pNext) &&
		 (pSubQuery->OptInfo.eOptType == QOPT_USING_INDEX) &&
		 (!pSubQuery->OptInfo.bDoRecMatch) &&
		 (!pSubQuery->bHaveDrnFlds))
	{
		*pbPositionable = TRUE;
	}
Exit:
	return( rc);
}
