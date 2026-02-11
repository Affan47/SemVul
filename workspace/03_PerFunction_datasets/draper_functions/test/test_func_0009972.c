FSDelParentElm(
	FDB *			pDb,
	LFILE *		pLFile,
	BTSK **	 	pStackRV)
{
	RCODE		rc;
	BTSK *	pStack = *pStackRV;

	pStack--;

	if (RC_BAD( rc = FSGetBlock( pDb, pLFile, pStack->uiBlkAddr, pStack)))
	{
		goto Exit;
	}


	if (RC_BAD( rc = FSBtScanTo( pStack, NULL, 0, (FLMUINT) 0)))
	{
		goto Exit;
	}


	rc = FSBtDelete( pDb, pLFile, &pStack);

Exit:

	pStack++;
	*pStackRV = pStack;

	return (rc);
}
