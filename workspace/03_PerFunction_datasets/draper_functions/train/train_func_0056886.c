gistXLogUpdate(RelFileNode node, Buffer buffer,
			   OffsetNumber *todelete, int ntodelete,
			   IndexTuple *itup, int ituplen,
			   Buffer leftchildbuf)
{
	XLogRecData *rdata;
	gistxlogPageUpdate *xlrec;
	int			cur,
				i;
	XLogRecPtr	recptr;

	rdata = (XLogRecData *) palloc(sizeof(XLogRecData) * (4 + ituplen));
	xlrec = (gistxlogPageUpdate *) palloc(sizeof(gistxlogPageUpdate));

	xlrec->node = node;
	xlrec->blkno = BufferGetBlockNumber(buffer);
	xlrec->ntodelete = ntodelete;
	xlrec->leftchild =
		BufferIsValid(leftchildbuf) ? BufferGetBlockNumber(leftchildbuf) : InvalidBlockNumber;

	rdata[0].buffer = buffer;
	rdata[0].buffer_std = true;
	rdata[0].data = NULL;
	rdata[0].len = 0;
	rdata[0].next = &(rdata[1]);

	rdata[1].data = (char *) xlrec;
	rdata[1].len = sizeof(gistxlogPageUpdate);
	rdata[1].buffer = InvalidBuffer;
	rdata[1].next = &(rdata[2]);

	rdata[2].data = (char *) todelete;
	rdata[2].len = sizeof(OffsetNumber) * ntodelete;
	rdata[2].buffer = buffer;
	rdata[2].buffer_std = true;

	cur = 3;


	for (i = 0; i < ituplen; i++)
	{
		rdata[cur - 1].next = &(rdata[cur]);
		rdata[cur].data = (char *) (itup[i]);
		rdata[cur].len = IndexTupleSize(itup[i]);
		rdata[cur].buffer = buffer;
		rdata[cur].buffer_std = true;
		cur++;
	}


	if (BufferIsValid(leftchildbuf))
	{
		rdata[cur - 1].next = &(rdata[cur]);
		rdata[cur].data = NULL;
		rdata[cur].len = 0;
		rdata[cur].buffer = leftchildbuf;
		rdata[cur].buffer_std = true;
		cur++;
	}
	rdata[cur - 1].next = NULL;

	recptr = XLogInsert(RM_GIST_ID, XLOG_GIST_PAGE_UPDATE, rdata);

	pfree(rdata);
	return recptr;
}
