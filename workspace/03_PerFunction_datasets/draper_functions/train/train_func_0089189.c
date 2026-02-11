KYAbortCurrentRecord(
	FDB *			pDb)
{
	flmAssert( pDb->KrefCntrl.bKrefSetup);


	if (pDb->pDict->uiIfdCnt)
	{
		f_memset( pDb->KrefCntrl.ppCdlTbl, 0,
					 pDb->pDict->uiIfdCnt * sizeof(CDL *));
	}

	if (pDb->pDict->uiIxdCnt)
	{
		f_memset( pDb->KrefCntrl.pIxHasCmpKeys, 0, pDb->pDict->uiIxdCnt);
	}

	pDb->KrefCntrl.uiCount = pDb->KrefCntrl.uiLastRecEnd;
	pDb->KrefCntrl.pPool->poolReset( pDb->KrefCntrl.pReset);
}
