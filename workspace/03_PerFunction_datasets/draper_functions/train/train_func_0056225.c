ResetSequence(Oid seq_relid)
{
	Relation	seq_rel;
	SeqTable	elm;
	Form_pg_sequence seq;
	Buffer		buf;
	Page		page;
	HeapTuple	tuple;
	HeapTupleData tupledata;
	ItemId		lp;


	init_sequence(seq_relid, &elm, &seq_rel);
	seq = read_info(elm, seq_rel, &buf);


	page = BufferGetPage(buf);
	lp = PageGetItemId(page, FirstOffsetNumber);
	Assert(ItemIdIsNormal(lp));

	tupledata.t_data = (HeapTupleHeader) PageGetItem(page, lp);
	tupledata.t_len = ItemIdGetLength(lp);
	tuple = heap_copytuple(&tupledata);


	UnlockReleaseBuffer(buf);


	seq = (Form_pg_sequence) GETSTRUCT(tuple);
	seq->last_value = seq->start_value;
	seq->is_called = false;
	seq->log_cnt = 1;


	RelationSetNewRelfilenode(seq_rel, InvalidTransactionId);


	fill_seq_with_data(seq_rel, tuple);


	elm->cached = elm->last;

	relation_close(seq_rel, NoLock);
}
