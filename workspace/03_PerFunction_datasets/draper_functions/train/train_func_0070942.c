fdictAddNewCCS(
	TDICT *			pTDict,
	TENCDEF *		pTEncDef,
	FLMUINT			uiRecNum)
{
	RCODE				rc = FERR_OK;
	FDICT *			pDict = pTDict->pDict;
	ITT *				pItt;
	F_CCS *			pCcs = NULL;
	FDB *				pDb = pTDict->pDb;
	F_CCS *			pDbWrappingKey;

	if( uiRecNum >= FLM_RESERVED_TAG_NUMS)
	{
		goto Exit;
	}

	if (!pDb->pFile->bInLimitedMode)
	{

		pDbWrappingKey = pDb->pFile->pDbWrappingKey;

		flmAssert( pTEncDef);

		if ((pCcs = f_new F_CCS) == NULL)
		{
			rc = RC_SET( FERR_MEM);
			goto Exit;
		}


		if (RC_BAD( rc = pCcs->init( FALSE, pTEncDef->uiAlgType )))
		{
			goto Exit;
		}

		if (!pTEncDef->uiLength)
		{
			flmAssert( 0);
			rc = RC_SET( FERR_MISSING_ENC_KEY);
			goto Exit;
		}


		if( RC_BAD( rc = pCcs->setKeyFromStore( pTEncDef->pucKeyInfo,
			(FLMUINT32)pTEncDef->uiLength, NULL, pDbWrappingKey)))
		{
			goto Exit;
		}
	}


	pItt = pDict->pIttTbl + uiRecNum;
	pItt->pvItem = (void *)pCcs;
	pCcs = NULL;

	if( uiRecNum >= pDict->uiIttCnt)
	{
		pDict->uiIttCnt = uiRecNum + 1;
	}

Exit:

	if (pCcs)
	{
		delete pCcs;
	}

	return( rc);

}
