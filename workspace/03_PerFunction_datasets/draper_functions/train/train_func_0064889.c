flmLoadPosKeys(
	CURSOR *		pCursor,
	POS_KEY *	pKeys,
	FLMUINT		uiNumKeys,
	FLMBOOL		bLeafLevel
	)
{
	RCODE		rc = FERR_OK;
	FLMUINT	uiKeyCnt;
	FLMUINT	uiRFactor;
	FLMUINT	uiTotCnt;


	if (!pKeys || !uiNumKeys)
	{
		goto Exit;
	}


	uiKeyCnt = (uiNumKeys > FLM_MAX_POS_KEYS + 1)
				? FLM_MAX_POS_KEYS + 1
				: uiNumKeys;
	if (RC_BAD( rc = f_calloc( uiKeyCnt * sizeof( POS_KEY),
										&pCursor->pPosKeyArray)))
	{
		goto Exit;
	}
	pCursor->uiNumPosKeys = uiKeyCnt;
	pCursor->bLeafLevel = bLeafLevel;


	if (uiNumKeys <= FLM_MAX_POS_KEYS + 1)
	{
		for (uiTotCnt = 0; uiTotCnt < uiKeyCnt; uiTotCnt++)
		{
			f_memcpy( &pCursor->pPosKeyArray[ uiTotCnt],
						 &pKeys[ uiTotCnt],
						 sizeof( POS_KEY));


			pKeys [uiTotCnt].pucKey = NULL;
		}
	}


	else
	{
		FLMUINT		uiLoopCnt;
		FLMUINT		uiIntervalSize = (uiNumKeys - 2) / (FLM_MAX_POS_KEYS - 1) - 1;

		uiRFactor = (uiNumKeys - 2) % (FLM_MAX_POS_KEYS - 1);

		f_memcpy( &pCursor->pPosKeyArray[ 0], &pKeys[ 0], sizeof( POS_KEY));
		f_memcpy( &pCursor->pPosKeyArray[ 1], &pKeys[ 1], sizeof( POS_KEY));


		pKeys [0].pucKey = NULL;
		pKeys [1].pucKey = NULL;

		uiKeyCnt = 2;
		for( uiTotCnt = 2; uiTotCnt < FLM_MAX_POS_KEYS; uiTotCnt++)
		{
			for( uiLoopCnt = 0; uiLoopCnt < uiIntervalSize; uiLoopCnt++)
			{
				f_free( &pKeys[ uiKeyCnt].pucKey);
				uiKeyCnt++;
			}

			if( uiRFactor)
			{
				f_free( &pKeys[ uiKeyCnt].pucKey);
				uiKeyCnt++;
				uiRFactor--;
			}

			f_memcpy( &pCursor->pPosKeyArray[ uiTotCnt],
						&pKeys[ uiKeyCnt], sizeof( POS_KEY));


			pKeys [uiKeyCnt].pucKey = NULL;
			uiKeyCnt++;
		}


		f_memcpy( &pCursor->pPosKeyArray[ FLM_MAX_POS_KEYS],
						&pKeys[ uiNumKeys - 1], sizeof( POS_KEY));
		pKeys [uiNumKeys - 1].pucKey = NULL;
		while (uiKeyCnt < uiNumKeys - 1)
		{
			f_free( &pKeys[ uiKeyCnt].pucKey);
			uiKeyCnt++;
		}
	}

Exit:
	return( rc);
}
