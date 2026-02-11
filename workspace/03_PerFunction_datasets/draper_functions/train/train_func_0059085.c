GetOldestActiveTransactionId(void)
{
	ProcArrayStruct *arrayP = procArray;
	TransactionId oldestRunningXid;
	int			index;

	Assert(!RecoveryInProgress());

	LWLockAcquire(ProcArrayLock, LW_SHARED);


	oldestRunningXid = ShmemVariableCache->nextXid;


	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		volatile PGXACT *pgxact = &allPgXact[pgprocno];
		TransactionId xid;


		xid = pgxact->xid;

		if (!TransactionIdIsNormal(xid))
			continue;

		if (TransactionIdPrecedes(xid, oldestRunningXid))
			oldestRunningXid = xid;


	}

	LWLockRelease(ProcArrayLock);

	return oldestRunningXid;
}
