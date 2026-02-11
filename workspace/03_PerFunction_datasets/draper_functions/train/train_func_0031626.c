FB_OperationEnd(
	FDB *       pDb,
	RCODE			rcOfOperation)
{
	RCODE				rc = FERR_OK;
	FlmBlobImp *	pBlob;


	if( !pDb || pDb->uiTransType == FLM_NO_TRANS)
	{
		goto Exit;
	}

	for( pBlob = pDb->pBlobList; pBlob; pBlob = pBlob->getNext())
	{
		pBlob->transitionAction( rcOfOperation == FERR_OK ? TRUE : FALSE);
	}

Exit:
	rc = (rcOfOperation != FERR_OK) ? rcOfOperation : rc;
	return( rc );
}
