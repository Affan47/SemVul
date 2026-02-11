FlmCursorTestDRN(
	HFCURSOR			hCursor,
	FLMUINT 			uiDrn,
	FLMBOOL * 		pbIsMatch)
{
	RCODE				rc = FERR_OK;
	FDB *				pDb = NULL;
	CURSOR *			pCursor = (CURSOR *)hCursor;
	SUBQUERY *		pSubQuery;
	FlmRecord *		pRec = NULL;

	flmAssert( pCursor != NULL);
	*pbIsMatch = FALSE;
	if (pCursor->pCSContext)
	{
		rc = flmCurCSTestRec( pCursor, uiDrn, NULL, pbIsMatch);
		goto Exit2;
	}

	flmAssert( pCursor->pDb != NULL);
	if (RC_OK( rc = FlmRecordRetrieve( (HFDB)pCursor->pDb,
							pCursor->uiContainer,
							uiDrn, FO_EXACT, &pRec, NULL)))
	{


		if (!pCursor->bOptimized)
		{
			if (RC_BAD( rc = flmCurPrep( pCursor)))
			{
				goto Exit;
			}
		}

		pDb = pCursor->pDb;
		if (RC_BAD(rc = flmCurDbInit( pCursor)))
		{
			goto Exit;
		}


		pSubQuery = pCursor->pSubQueryList;
		while (pSubQuery)
		{
			FLMUINT	uiResult;

			if (RC_BAD( rc = flmCurEvalCriteria( pCursor, pSubQuery,
										pRec, FALSE, &uiResult)))
			{
				goto Exit;
			}
			if (uiResult == FLM_TRUE)
			{
				*pbIsMatch = TRUE;
				break;
			}
			pSubQuery = pSubQuery->pNext;
		}

	}

Exit:

	if (pDb)
	{
		fdbExit( pDb);
	}

	if (pRec)
	{
		pRec->Release();
	}

Exit2:
	return( rc);
}
