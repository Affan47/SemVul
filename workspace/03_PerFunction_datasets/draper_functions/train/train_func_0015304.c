FlmDbTransAbort(
	HFDB			hDb)
{
	RCODE			rc;
	FDB *			pDb = (FDB *)hDb;
	FLMBOOL		bIgnore;

	if (IsInCSMode( hDb))
	{
		fdbInitCS( pDb);
		FCL_WIRE	Wire( pDb->pCSContext, pDb);
		if (!pDb->pCSContext->bConnectionGood)
		{
			rc = RC_SET( FERR_BAD_SERVER_CONNECTION);
		}
		else
		{
			rc = Wire.doTransOp( FCS_OP_TRANSACTION_ABORT, 0, 0, 0);
		}
		goto Exit;
	}

	if (RC_BAD( rc = fdbInit( pDb, FLM_NO_TRANS,
		FDB_TRANS_GOING_OK | FDB_CLOSING_OK, 0, &bIgnore)))
	{
		goto Exit;
	}


	if ((pDb->uiTransType == FLM_NO_TRANS) ||
		 (pDb->uiFlags & FDB_INVISIBLE_TRANS))
	{
		rc = RC_SET( FERR_NO_TRANS_ACTIVE);
		goto Exit;
	}

	rc = flmAbortDbTrans( pDb);

Exit:

	if( RC_OK( rc))
	{
		rc = flmCheckDatabaseState( pDb);
	}

	flmExit( FLM_DB_TRANS_ABORT, pDb, rc);
	return( rc);
}
