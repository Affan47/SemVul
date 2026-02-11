flmAllocFdb(
	FDB **		ppDb)
{
	RCODE			rc = FERR_OK;
	FDB *			pDb = NULL;


	*ppDb = NULL;
	if( RC_BAD( rc = f_calloc( sizeof( FDB), ppDb)))
	{
		goto Exit;
	}

	pDb = *ppDb;
	pDb->hWaitSem = F_SEM_NULL;


	pDb->tmpKrefPool.poolInit( 8192);
	pDb->TempPool.poolInit( MAX_KEY_SIZ * 4);

#if defined( FLM_DEBUG)


	pDb->hMutex = F_MUTEX_NULL;
	if (RC_BAD( rc = f_mutexCreate( &pDb->hMutex)))
	{
		goto Exit;
	}
#endif

	if( RC_BAD( rc = f_semCreate( &pDb->hWaitSem)))
	{
		goto Exit;
	}

	if( RC_BAD( rc = f_allocAlignedBuffer( MAX_BLOCK_SIZE,
		&pDb->pucAlignedReadBuf)))
	{
		goto Exit;
	}


	if( RC_BAD( rc = flmStatInit( &pDb->Stats, FALSE)))
	{
		goto Exit;
	}
	pDb->bStatsInitialized = TRUE;

Exit:

	if (RC_BAD( rc) && pDb)
	{
		flmDbClose( (HFDB *)ppDb, FALSE);
	}
	return( rc);
}
