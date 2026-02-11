fdictCreateNewDict(
	FDB *			pDb)
{
	RCODE			rc = FERR_OK;


	if( pDb->pDict)
	{
		f_mutexLock( gv_FlmSysData.hShareMutex);
		flmUnlinkFdbFromDict( pDb);
		f_mutexUnlock( gv_FlmSysData.hShareMutex);
	}


	if( RC_BAD( rc = fdictRebuild( pDb)))
	{
		goto Exit;
	}


	pDb->uiFlags |= FDB_UPDATED_DICTIONARY;

Exit:


	if( (RC_BAD( rc)) && (pDb->pDict))
	{
		flmFreeDict( pDb->pDict);
		pDb->pDict = NULL;
	}

	return( rc);
}
