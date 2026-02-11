log_heap_update(Relation reln, Buffer oldbuf, ItemPointerData from,
				Buffer newbuf, HeapTuple newtup,
				bool all_visible_cleared, bool new_all_visible_cleared)
{
	xl_heap_update xlrec;
	xl_heap_header xlhdr;
	uint8		info;
	XLogRecPtr	recptr;
	XLogRecData rdata[4];
	Page		page = BufferGetPage(newbuf);


	Assert(RelationNeedsWAL(reln));

	if (HeapTupleIsHeapOnly(newtup))
		info = XLOG_HEAP_HOT_UPDATE;
	else
		info = XLOG_HEAP_UPDATE;

	xlrec.target.node = reln->rd_node;
	xlrec.target.tid = from;
	xlrec.all_visible_cleared = all_visible_cleared;
	xlrec.newtid = newtup->t_self;
	xlrec.new_all_visible_cleared = new_all_visible_cleared;

	rdata[0].data = (char *) &xlrec;
	rdata[0].len = SizeOfHeapUpdate;
	rdata[0].buffer = InvalidBuffer;
	rdata[0].next = &(rdata[1]);

	rdata[1].data = NULL;
	rdata[1].len = 0;
	rdata[1].buffer = oldbuf;
	rdata[1].buffer_std = true;
	rdata[1].next = &(rdata[2]);

	xlhdr.t_infomask2 = newtup->t_data->t_infomask2;
	xlhdr.t_infomask = newtup->t_data->t_infomask;
	xlhdr.t_hoff = newtup->t_data->t_hoff;


	rdata[2].data = (char *) &xlhdr;
	rdata[2].len = SizeOfHeapHeader;
	rdata[2].buffer = newbuf;
	rdata[2].buffer_std = true;
	rdata[2].next = &(rdata[3]);


	rdata[3].data = (char *) newtup->t_data + offsetof(HeapTupleHeaderData, t_bits);
	rdata[3].len = newtup->t_len - offsetof(HeapTupleHeaderData, t_bits);
	rdata[3].buffer = newbuf;
	rdata[3].buffer_std = true;
	rdata[3].next = NULL;


	if (ItemPointerGetOffsetNumber(&(newtup->t_self)) == FirstOffsetNumber &&
		PageGetMaxOffsetNumber(page) == FirstOffsetNumber)
	{
		info |= XLOG_HEAP_INIT_PAGE;
		rdata[2].buffer = rdata[3].buffer = InvalidBuffer;
	}

	recptr = XLogInsert(RM_HEAP_ID, info, rdata);

	return recptr;
}
