flmIndexingAfterAbort(
	FDB *					pDb)
{
	F_BKGND_IX *		pStartIx;
	F_BKGND_IX *		pStopIx;
	F_BKGND_IX *		pNextIx;

	pStopIx = pDb->pIxStopList;
	pDb->pIxStopList = NULL;
	for( ; pStopIx; pStopIx = pNextIx)
	{
		pNextIx = pStopIx->pNext;
		f_free( &pStopIx);
	}

	pStartIx = pDb->pIxStartList;
	pDb->pIxStartList = NULL;
	for( ; pStartIx; pStartIx = pNextIx)
	{
		pNextIx = pStartIx->pNext;
		f_free( &pStartIx);
	}
}
