standby_redo(XLogRecPtr lsn, XLogRecord *record)
{
	uint8		info = record->xl_info & ~XLR_INFO_MASK;


	if (standbyState == STANDBY_DISABLED)
		return;

	if (info == XLOG_STANDBY_LOCK)
	{
		xl_standby_locks *xlrec = (xl_standby_locks *) XLogRecGetData(record);
		int			i;

		for (i = 0; i < xlrec->nlocks; i++)
			StandbyAcquireAccessExclusiveLock(xlrec->locks[i].xid,
											  xlrec->locks[i].dbOid,
											  xlrec->locks[i].relOid);
	}
	else if (info == XLOG_RUNNING_XACTS)
	{
		xl_running_xacts *xlrec = (xl_running_xacts *) XLogRecGetData(record);
		RunningTransactionsData running;

		running.xcnt = xlrec->xcnt;
		running.subxid_overflow = xlrec->subxid_overflow;
		running.nextXid = xlrec->nextXid;
		running.latestCompletedXid = xlrec->latestCompletedXid;
		running.oldestRunningXid = xlrec->oldestRunningXid;
		running.xids = xlrec->xids;

		ProcArrayApplyRecoveryInfo(&running);
	}
	else
		elog(PANIC, "relation_redo: unknown op code %u", info);
}
