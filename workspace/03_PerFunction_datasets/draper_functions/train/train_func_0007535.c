SetTransactionIdLimit(TransactionId oldest_datfrozenxid,
					  Name oldest_datname)
{
	TransactionId xidVacLimit;
	TransactionId xidWarnLimit;
	TransactionId xidStopLimit;
	TransactionId xidWrapLimit;
	TransactionId curXid;

	Assert(TransactionIdIsNormal(oldest_datfrozenxid));


	xidWrapLimit = oldest_datfrozenxid + (MaxTransactionId >> 1);
	if (xidWrapLimit < FirstNormalTransactionId)
		xidWrapLimit += FirstNormalTransactionId;


	xidStopLimit = xidWrapLimit - 1000000;
	if (xidStopLimit < FirstNormalTransactionId)
		xidStopLimit -= FirstNormalTransactionId;


	xidWarnLimit = xidStopLimit - 10000000;
	if (xidWarnLimit < FirstNormalTransactionId)
		xidWarnLimit -= FirstNormalTransactionId;


	xidVacLimit = oldest_datfrozenxid + autovacuum_freeze_max_age;
	if (xidVacLimit < FirstNormalTransactionId)
		xidVacLimit += FirstNormalTransactionId;


	LWLockAcquire(XidGenLock, LW_EXCLUSIVE);
	ShmemVariableCache->oldestXid = oldest_datfrozenxid;
	ShmemVariableCache->xidVacLimit = xidVacLimit;
	ShmemVariableCache->xidWarnLimit = xidWarnLimit;
	ShmemVariableCache->xidStopLimit = xidStopLimit;
	ShmemVariableCache->xidWrapLimit = xidWrapLimit;
	namecpy(&ShmemVariableCache->limit_datname, oldest_datname);
	curXid = ShmemVariableCache->nextXid;
	LWLockRelease(XidGenLock);


	ereport(DEBUG1,
	   (errmsg("transaction ID wrap limit is %u, limited by database \"%s\"",
			   xidWrapLimit, NameStr(*oldest_datname))));


	if (TransactionIdFollowsOrEquals(curXid, xidVacLimit) &&
		IsUnderPostmaster)
		SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);


	if (TransactionIdFollowsOrEquals(curXid, xidWarnLimit))
		ereport(WARNING,
		   (errmsg("database \"%s\" must be vacuumed within %u transactions",
				   NameStr(*oldest_datname),
				   xidWrapLimit - curXid),
			errhint("To avoid a database shutdown, execute a full-database VACUUM in \"%s\".",
					NameStr(*oldest_datname))));
}
