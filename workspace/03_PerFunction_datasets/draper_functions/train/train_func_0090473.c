GetNewTransactionId(bool isSubXact)
{
	TransactionId xid;


	if (IsBootstrapProcessingMode())
	{
		Assert(!isSubXact);
		MyProc->xid = BootstrapTransactionId;
		return BootstrapTransactionId;
	}

	LWLockAcquire(XidGenLock, LW_EXCLUSIVE);

	xid = ShmemVariableCache->nextXid;


	if (TransactionIdFollowsOrEquals(xid, ShmemVariableCache->xidVacLimit) &&
		TransactionIdIsValid(ShmemVariableCache->xidVacLimit))
	{


		if (IsUnderPostmaster && (xid % 65536) == 0)
			SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);

		if (IsUnderPostmaster &&
		 TransactionIdFollowsOrEquals(xid, ShmemVariableCache->xidStopLimit))
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("database is not accepting commands to avoid wraparound data loss in database \"%s\"",
							NameStr(ShmemVariableCache->limit_datname)),
					 errhint("Stop the postmaster and use a standalone backend to vacuum database \"%s\".",
							 NameStr(ShmemVariableCache->limit_datname))));
		else if (TransactionIdFollowsOrEquals(xid, ShmemVariableCache->xidWarnLimit))
			ereport(WARNING,
			(errmsg("database \"%s\" must be vacuumed within %u transactions",
					NameStr(ShmemVariableCache->limit_datname),
					ShmemVariableCache->xidWrapLimit - xid),
			 errhint("To avoid a database shutdown, execute a full-database VACUUM in \"%s\".",
					 NameStr(ShmemVariableCache->limit_datname))));
	}


	ExtendCLOG(xid);
	ExtendSUBTRANS(xid);


	TransactionIdAdvance(ShmemVariableCache->nextXid);


	{


		volatile PGPROC *myproc = MyProc;

		if (!isSubXact)
			myproc->xid = xid;
		else
		{
			int			nxids = myproc->subxids.nxids;

			if (nxids < PGPROC_MAX_CACHED_SUBXIDS)
			{
				myproc->subxids.xids[nxids] = xid;
				myproc->subxids.nxids = nxids + 1;
			}
			else
				myproc->subxids.overflowed = true;
		}
	}

	LWLockRelease(XidGenLock);

	return xid;
}
