multixact_redo(XLogRecPtr lsn, XLogRecord *record)
{
	uint8		info = record->xl_info & ~XLR_INFO_MASK;


	Assert(!(record->xl_info & XLR_BKP_BLOCK_MASK));

	if (info == XLOG_MULTIXACT_ZERO_OFF_PAGE)
	{
		int			pageno;
		int			slotno;

		memcpy(&pageno, XLogRecGetData(record), sizeof(int));

		LWLockAcquire(MultiXactOffsetControlLock, LW_EXCLUSIVE);

		slotno = ZeroMultiXactOffsetPage(pageno, false);
		SimpleLruWritePage(MultiXactOffsetCtl, slotno, NULL);
		Assert(!MultiXactOffsetCtl->shared->page_dirty[slotno]);

		LWLockRelease(MultiXactOffsetControlLock);
	}
	else if (info == XLOG_MULTIXACT_ZERO_MEM_PAGE)
	{
		int			pageno;
		int			slotno;

		memcpy(&pageno, XLogRecGetData(record), sizeof(int));

		LWLockAcquire(MultiXactMemberControlLock, LW_EXCLUSIVE);

		slotno = ZeroMultiXactMemberPage(pageno, false);
		SimpleLruWritePage(MultiXactMemberCtl, slotno, NULL);
		Assert(!MultiXactMemberCtl->shared->page_dirty[slotno]);

		LWLockRelease(MultiXactMemberControlLock);
	}
	else if (info == XLOG_MULTIXACT_CREATE_ID)
	{
		xl_multixact_create *xlrec = (xl_multixact_create *) XLogRecGetData(record);
		TransactionId *xids = xlrec->xids;
		TransactionId max_xid;
		int			i;


		RecordNewMultiXact(xlrec->mid, xlrec->moff, xlrec->nxids, xids);


		MultiXactAdvanceNextMXact(xlrec->mid + 1, xlrec->moff + xlrec->nxids);


		max_xid = record->xl_xid;
		for (i = 0; i < xlrec->nxids; i++)
		{
			if (TransactionIdPrecedes(max_xid, xids[i]))
				max_xid = xids[i];
		}


		if (TransactionIdFollowsOrEquals(max_xid,
										 ShmemVariableCache->nextXid))
		{
			LWLockAcquire(XidGenLock, LW_EXCLUSIVE);
			ShmemVariableCache->nextXid = max_xid;
			TransactionIdAdvance(ShmemVariableCache->nextXid);
			LWLockRelease(XidGenLock);
		}
	}
	else
		elog(PANIC, "multixact_redo: unknown op code %u", info);
}
