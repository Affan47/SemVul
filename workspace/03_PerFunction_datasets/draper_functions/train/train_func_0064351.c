FlmDbGetLockType(
	HFDB				hDb,
	eLockType *		pLockType,
	FLMBOOL *		pbImplicit)
{
	RCODE		rc = FERR_OK;
	FDB *		pDb = NULL;
	FLMBOOL	bIgnore;

	if( pLockType)
	{
		*pLockType = FLM_LOCK_NONE;
	}

	if( pbImplicit)
	{
		*pbImplicit = FALSE;
	}

	if (IsInCSMode( hDb))
	{
		rc = RC_SET( FERR_NOT_IMPLEMENTED);
		goto Exit;
	}

	pDb = (FDB *)hDb;
	if (RC_BAD( rc = fdbInit( pDb, FLM_NO_TRANS,
									  FDB_TRANS_GOING_OK, 0, &bIgnore)))
	{
		goto Exit;
	}

	if( pDb->uiFlags & FDB_HAS_FILE_LOCK)
	{
		if( pLockType)
		{
			if( pDb->uiFlags & FDB_FILE_LOCK_SHARED)
			{
				*pLockType = FLM_LOCK_SHARED;
			}
			else
			{
				*pLockType = FLM_LOCK_EXCLUSIVE;
			}
		}

		if( pbImplicit)
		{
			*pbImplicit = (pDb->uiFlags & FDB_FILE_LOCK_IMPLICIT)
								? TRUE
								: FALSE;
		}
	}

Exit:

	flmExit( FLM_DB_GET_LOCK_TYPE, pDb, rc);
	return( rc);
}
