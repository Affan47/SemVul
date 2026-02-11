TransactionIdSetTreeStatus(TransactionId xid, int nsubxids,
					TransactionId *subxids, XidStatus status, XLogRecPtr lsn)
{
	int			pageno = TransactionIdToPage(xid);
	int			i;

	Assert(status == TRANSACTION_STATUS_COMMITTED ||
		   status == TRANSACTION_STATUS_ABORTED);


	for (i = 0; i < nsubxids; i++)
	{
		if (TransactionIdToPage(subxids[i]) != pageno)
			break;
	}


	if (i == nsubxids)
	{


		TransactionIdSetPageStatus(xid, nsubxids, subxids, status, lsn,
								   pageno);
	}
	else
	{
		int			nsubxids_on_first_page = i;


		if (status == TRANSACTION_STATUS_COMMITTED)
			set_status_by_pages(nsubxids - nsubxids_on_first_page,
								subxids + nsubxids_on_first_page,
								TRANSACTION_STATUS_SUB_COMMITTED, lsn);


		pageno = TransactionIdToPage(xid);
		TransactionIdSetPageStatus(xid, nsubxids_on_first_page, subxids, status,
								   lsn, pageno);


		set_status_by_pages(nsubxids - nsubxids_on_first_page,
							subxids + nsubxids_on_first_page,
							status, lsn);
	}
}
