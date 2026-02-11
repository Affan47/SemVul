set_status_by_pages(int nsubxids, TransactionId *subxids,
					XidStatus status, XLogRecPtr lsn)
{
	int			pageno = TransactionIdToPage(subxids[0]);
	int			offset = 0;
	int			i = 0;

	while (i < nsubxids)
	{
		int			num_on_page = 0;

		while (TransactionIdToPage(subxids[i]) == pageno && i < nsubxids)
		{
			num_on_page++;
			i++;
		}

		TransactionIdSetPageStatus(InvalidTransactionId,
								   num_on_page, subxids + offset,
								   status, lsn, pageno);
		offset = i;
		pageno = TransactionIdToPage(subxids[offset]);
	}
}
