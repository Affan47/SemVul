log_heap_clean(Relation reln, Buffer buffer,
			   OffsetNumber *redirected, int nredirected,
			   OffsetNumber *nowdead, int ndead,
			   OffsetNumber *nowunused, int nunused,
			   TransactionId latestRemovedXid)
{
	xl_heap_clean xlrec;
	uint8		info;
	XLogRecPtr	recptr;
	XLogRecData rdata[4];


	Assert(RelationNeedsWAL(reln));

	xlrec.node = reln->rd_node;
	xlrec.block = BufferGetBlockNumber(buffer);
	xlrec.latestRemovedXid = latestRemovedXid;
	xlrec.nredirected = nredirected;
	xlrec.ndead = ndead;

	rdata[0].data = (char *) &xlrec;
	rdata[0].len = SizeOfHeapClean;
	rdata[0].buffer = InvalidBuffer;
	rdata[0].next = &(rdata[1]);


	if (nredirected > 0)
	{
		rdata[1].data = (char *) redirected;
		rdata[1].len = nredirected * sizeof(OffsetNumber) * 2;
	}
	else
	{
		rdata[1].data = NULL;
		rdata[1].len = 0;
	}
	rdata[1].buffer = buffer;
	rdata[1].buffer_std = true;
	rdata[1].next = &(rdata[2]);

	if (ndead > 0)
	{
		rdata[2].data = (char *) nowdead;
		rdata[2].len = ndead * sizeof(OffsetNumber);
	}
	else
	{
		rdata[2].data = NULL;
		rdata[2].len = 0;
	}
	rdata[2].buffer = buffer;
	rdata[2].buffer_std = true;
	rdata[2].next = &(rdata[3]);

	if (nunused > 0)
	{
		rdata[3].data = (char *) nowunused;
		rdata[3].len = nunused * sizeof(OffsetNumber);
	}
	else
	{
		rdata[3].data = NULL;
		rdata[3].len = 0;
	}
	rdata[3].buffer = buffer;
	rdata[3].buffer_std = true;
	rdata[3].next = NULL;

	info = XLOG_HEAP2_CLEAN;
	recptr = XLogInsert(RM_HEAP2_ID, info, rdata);

	return recptr;
}
