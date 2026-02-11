log_heap_freeze(Relation reln, Buffer buffer,
				TransactionId cutoff_xid,
				OffsetNumber *offsets, int offcnt)
{
	xl_heap_freeze xlrec;
	XLogRecPtr	recptr;
	XLogRecData rdata[2];


	Assert(!reln->rd_istemp);

	xlrec.node = reln->rd_node;
	xlrec.block = BufferGetBlockNumber(buffer);
	xlrec.cutoff_xid = cutoff_xid;

	rdata[0].data = (char *) &xlrec;
	rdata[0].len = SizeOfHeapFreeze;
	rdata[0].buffer = InvalidBuffer;
	rdata[0].next = &(rdata[1]);


	if (offcnt > 0)
	{
		rdata[1].data = (char *) offsets;
		rdata[1].len = offcnt * sizeof(OffsetNumber);
	}
	else
	{
		rdata[1].data = NULL;
		rdata[1].len = 0;
	}
	rdata[1].buffer = buffer;
	rdata[1].buffer_std = true;
	rdata[1].next = NULL;

	recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_FREEZE, rdata);

	return recptr;
}
