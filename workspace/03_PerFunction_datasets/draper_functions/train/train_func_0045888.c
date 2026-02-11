LogCurrentRunningXacts(RunningTransactions CurrRunningXacts)
{
	xl_running_xacts xlrec;
	XLogRecPtr	recptr;

	xlrec.xcnt = CurrRunningXacts->xcnt;
	xlrec.subxcnt = CurrRunningXacts->subxcnt;
	xlrec.subxid_overflow = CurrRunningXacts->subxid_overflow;
	xlrec.nextXid = CurrRunningXacts->nextXid;
	xlrec.oldestRunningXid = CurrRunningXacts->oldestRunningXid;
	xlrec.latestCompletedXid = CurrRunningXacts->latestCompletedXid;


	XLogBeginInsert();
	XLogRegisterData((char *) (&xlrec), MinSizeOfXactRunningXacts);


	if (xlrec.xcnt > 0)
		XLogRegisterData((char *) CurrRunningXacts->xids,
					   (xlrec.xcnt + xlrec.subxcnt) * sizeof(TransactionId));

	recptr = XLogInsert(RM_STANDBY_ID, XLOG_RUNNING_XACTS);

	if (CurrRunningXacts->subxid_overflow)
		elog(trace_recovery(DEBUG2),
			 "snapshot of %u running transactions overflowed (lsn %X/%X oldest xid %u latest complete %u next xid %u)",
			 CurrRunningXacts->xcnt,
			 (uint32) (recptr >> 32), (uint32) recptr,
			 CurrRunningXacts->oldestRunningXid,
			 CurrRunningXacts->latestCompletedXid,
			 CurrRunningXacts->nextXid);
	else
		elog(trace_recovery(DEBUG2),
			 "snapshot of %u+%u running transaction ids (lsn %X/%X oldest xid %u latest complete %u next xid %u)",
			 CurrRunningXacts->xcnt, CurrRunningXacts->subxcnt,
			 (uint32) (recptr >> 32), (uint32) recptr,
			 CurrRunningXacts->oldestRunningXid,
			 CurrRunningXacts->latestCompletedXid,
			 CurrRunningXacts->nextXid);


	XLogSetAsyncXactLSN(recptr);

	return recptr;
}
