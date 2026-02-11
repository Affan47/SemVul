queryStatusCB(
	FLMUINT	uiStatusType,
	void *	pvParm1,
	void *,
	void *	pvUserData)
{
	RCODE		rc = FERR_OK;
	FLMUINT	uiCurrTime;

	switch (uiStatusType)
	{
		case FLM_SUBQUERY_STATUS:
		{
			FCURSOR_SUBQUERY_STATUS *	pQueryInfo = (FCURSOR_SUBQUERY_STATUS *)pvParm1;
			QUERY_STATUS *					pQueryStatus = (QUERY_STATUS *)pvUserData;

			pQueryStatus->uiProcessedCnt = pQueryInfo->uiProcessedCnt;
			uiCurrTime = FLM_GET_TIMER();
			if (pQueryStatus->bStopQuery)
			{
				rc = RC_SET( FERR_USER_ABORT);
				goto Exit;
			}
			else if (FLM_ELAPSED_TIME( uiCurrTime,
							pQueryStatus->uiLastTimeChecked) >=
					pQueryStatus->uiQueryTimeout)
			{
				rc = RC_SET( FERR_TIMEOUT);
				goto Exit;
			}
		}
	}

Exit:

	return( rc);
}
