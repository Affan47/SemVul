GetNextXidAndEpoch(TransactionId *xid, uint32 *epoch)
{
	uint32		ckptXidEpoch;
	TransactionId ckptXid;
	TransactionId nextXid;


	SpinLockAcquire(&XLogCtl->info_lck);
	ckptXidEpoch = XLogCtl->ckptXidEpoch;
	ckptXid = XLogCtl->ckptXid;
	SpinLockRelease(&XLogCtl->info_lck);


	nextXid = ReadNewTransactionId();


	if (nextXid < ckptXid)
		ckptXidEpoch++;

	*xid = nextXid;
	*epoch = ckptXidEpoch;
}
