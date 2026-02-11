log_heap_clean(Relation reln, Buffer buffer, OffsetNumber *unused, int uncnt)
{
	xl_heap_clean xlrec;
	XLogRecPtr	recptr;
	XLogRecData rdata[2];


	Assert(!reln->rd_istemp);

	xlrec.node = reln->rd_node;
	xlrec.block = BufferGetBlockNumber(buffer);

	rdata[0].data = (char *) &xlrec;
	rdata[0].len = SizeOfHeapClean;
	rdata[0].buffer = InvalidBuffer;
	rdata[0].next = &(rdata[1]);


	if (uncnt > 0)
	{
		rdata[1].data = (char *) unused;
		rdata[1].len = uncnt * sizeof(OffsetNumber);
	}
	else
	{
		rdata[1].data = NULL;
		rdata[1].len = 0;
	}
	rdata[1].buffer = buffer;
	rdata[1].buffer_std = true;
	rdata[1].next = NULL;

	recptr = XLogInsert(RM_HEAP_ID, XLOG_HEAP_CLEAN, rdata);

	return recptr;
}
