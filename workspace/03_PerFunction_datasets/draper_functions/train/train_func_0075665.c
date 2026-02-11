flmCurSearchContainer(
	eFlmFuncs	eFlmFuncId,
	CURSOR *		pCursor,
	FLMBOOL		bFirstRead,
	FLMBOOL		bReadForward,
	SUBQUERY *	pSubQuery,
	FLMUINT *	puiCount,
	FLMUINT *	puiSkipCount
	)
{
	RCODE					rc = FERR_OK;
	FDB *					pDb = pCursor->pDb;
	FSDataCursor *		pFSDataCursor = pSubQuery->pFSDataCursor;
	FLMUINT				uiCBTimer = 0;
	FLMUINT				uiCurrCBTime;
	FLMBOOL				bReturnRecOK;
	FLMUINT				uiCPUReleaseCnt = 0;
	FLMBOOL				bSavedInvisTrans;
	FLMUINT				uiStartTime = FLM_GET_TIMER();
	FLMUINT				uiCurrTime;
	FLMUINT				uiTimeLimit = pCursor->uiTimeLimit;
	FLMUINT				uiRecMatch;

	if (pCursor->fnStatus)
	{
		uiCBTimer = FLM_SECS_TO_TIMER_UNITS( STATUS_CB_INTERVAL);
	}


	pSubQuery->uiDrn = 0;


	for (;;)
	{


		if (((++uiCPUReleaseCnt) & 0x1F) == 0)
		{
			f_yieldCPU();
		}


		if (uiTimeLimit)
		{
			uiCurrTime = FLM_GET_TIMER();


			if (FLM_ELAPSED_TIME( uiCurrTime, uiStartTime) > uiTimeLimit)
			{
				rc = RC_SET( FERR_TIMEOUT);
				goto Exit;
			}
		}


		pSubQuery->SQStatus.uiProcessedCnt++;
		if (pCursor->fnStatus)
		{
			uiCurrCBTime = FLM_GET_TIMER();
			if (FLM_ELAPSED_TIME( uiCurrCBTime,
						pCursor->uiLastCBTime) > uiCBTimer)
			{
				CB_ENTER( pDb, &bSavedInvisTrans);
				rc = (pCursor->fnStatus)( FLM_SUBQUERY_STATUS,
										(void *)&pSubQuery->SQStatus,
										(void *)FALSE,
										pCursor->StatusData);
				CB_EXIT( pDb, bSavedInvisTrans);

				if (RC_BAD( rc))
				{
					goto Exit;
				}
				pCursor->uiLastCBTime = FLM_GET_TIMER();
			}
		}


		if (bFirstRead)
		{
			rc = (RCODE)((bReadForward)
							 ? pFSDataCursor->firstRec( pDb,
										&pSubQuery->pRec, &pSubQuery->uiDrn)
							 : pFSDataCursor->lastRec( pDb,
										&pSubQuery->pRec, &pSubQuery->uiDrn));
			if (RC_OK( rc))
			{
				bFirstRead = FALSE;
			}
		}
		else
		{
			rc = (RCODE)((bReadForward)
							 ? pFSDataCursor->nextRec( pDb,
														&pSubQuery->pRec, &pSubQuery->uiDrn)
							 : pFSDataCursor->prevRec( pDb,
														&pSubQuery->pRec, &pSubQuery->uiDrn));
		}
		if (RC_BAD( rc))
		{
			goto Exit;
		}
		pSubQuery->SQStatus.uiRecsFetchedForEval++;
		pSubQuery->bRecIsAKey = FALSE;


		if (RC_BAD( rc = flmCurEvalCriteria( pCursor, pSubQuery,
								pSubQuery->pRec, FALSE, &uiRecMatch)))
		{
			goto Exit;
		}

		if (uiRecMatch != FLM_TRUE)
		{
			pSubQuery->SQStatus.uiRecsRejected++;


			continue;
		}


		if (RC_BAD( rc = flmCurRecValidate( eFlmFuncId, pCursor,
									pSubQuery, puiSkipCount, puiCount,
									&bReturnRecOK)))
		{
			goto Exit;
		}
		if (bReturnRecOK)
		{
			break;
		}
	}

Exit:
	return( rc);
}
