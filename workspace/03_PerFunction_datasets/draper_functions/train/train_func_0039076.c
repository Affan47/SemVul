read_info(SeqTable elm, Relation rel, Buffer *buf)
{
	PageHeader	page;
	ItemId		lp;
	HeapTupleData tuple;
	sequence_magic *sm;
	Form_pg_sequence seq;

	*buf = ReadBuffer(rel, 0);
	LockBuffer(*buf, BUFFER_LOCK_EXCLUSIVE);

	page = (PageHeader) BufferGetPage(*buf);
	sm = (sequence_magic *) PageGetSpecialPointer(page);

	if (sm->magic != SEQ_MAGIC)
		elog(ERROR, "bad magic number in sequence \"%s\": %08X",
			 RelationGetRelationName(rel), sm->magic);

	lp = PageGetItemId(page, FirstOffsetNumber);
	Assert(ItemIdIsNormal(lp));
	tuple.t_data = (HeapTupleHeader) PageGetItem((Page) page, lp);

	seq = (Form_pg_sequence) GETSTRUCT(&tuple);


	elm->increment = seq->increment_by;

	return seq;
}
