ExpireTreeKnownAssignedTransactionIds(TransactionId xid, int nsubxids,
							   TransactionId *subxids, TransactionId max_xid)
{
	Assert(standbyState >= STANDBY_INITIALIZED);


	LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);

	KnownAssignedXidsRemoveTree(xid, nsubxids, subxids);


	if (TransactionIdPrecedes(ShmemVariableCache->latestCompletedXid,
							  max_xid))
		ShmemVariableCache->latestCompletedXid = max_xid;

	LWLockRelease(ProcArrayLock);
}
