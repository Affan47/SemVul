TransactionIdSetPageStatus(TransactionId xid, int nsubxids,
						   TransactionId *subxids, XidStatus status,
						   XLogRecPtr lsn, int pageno)
{
	int			slotno;
	int			i;

	Assert(status == TRANSACTION_STATUS_COMMITTED ||
		   status == TRANSACTION_STATUS_ABORTED ||
		   (status == TRANSACTION_STATUS_SUB_COMMITTED && !TransactionIdIsValid(xid)));

	LWLockAcquire(CLogControlLock, LW_EXCLUSIVE);


	slotno = SimpleLruReadPage(ClogCtl, pageno, XLogRecPtrIsInvalid(lsn), xid);


	if (TransactionIdIsValid(xid))
	{

		if (status == TRANSACTION_STATUS_COMMITTED)
		{
			for (i = 0; i < nsubxids; i++)
			{
				Assert(ClogCtl->shared->page_number[slotno] == TransactionIdToPage(subxids[i]));
				TransactionIdSetStatusBit(subxids[i],
										  TRANSACTION_STATUS_SUB_COMMITTED,
										  lsn, slotno);
			}
		}


		TransactionIdSetStatusBit(xid, status, lsn, slotno);
	}


	for (i = 0; i < nsubxids; i++)
	{
		Assert(ClogCtl->shared->page_number[slotno] == TransactionIdToPage(subxids[i]));
		TransactionIdSetStatusBit(subxids[i], status, lsn, slotno);
	}

	ClogCtl->shared->page_dirty[slotno] = true;

	LWLockRelease(CLogControlLock);
}
