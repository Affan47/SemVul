heap_release_fetch(Relation relation,
				   Snapshot snapshot,
				   HeapTuple tuple,
				   Buffer *userbuf,
				   bool keep_buf,
				   PgStat_Info *pgstat_info)
{
	ItemPointer tid = &(tuple->t_self);
	ItemId		lp;
	Buffer		buffer;
	PageHeader	dp;
	OffsetNumber offnum;
	bool		valid;


	buffer = ReleaseAndReadBuffer(*userbuf, relation,
								  ItemPointerGetBlockNumber(tid));


	LockBuffer(buffer, BUFFER_LOCK_SHARE);
	dp = (PageHeader) BufferGetPage(buffer);


	offnum = ItemPointerGetOffsetNumber(tid);
	if (offnum < FirstOffsetNumber || offnum > PageGetMaxOffsetNumber(dp))
	{
		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
		if (keep_buf)
			*userbuf = buffer;
		else
		{
			ReleaseBuffer(buffer);
			*userbuf = InvalidBuffer;
		}
		tuple->t_data = NULL;
		return false;
	}


	lp = PageGetItemId(dp, offnum);


	if (!ItemIdIsUsed(lp))
	{
		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
		if (keep_buf)
			*userbuf = buffer;
		else
		{
			ReleaseBuffer(buffer);
			*userbuf = InvalidBuffer;
		}
		tuple->t_data = NULL;
		return false;
	}


	tuple->t_data = (HeapTupleHeader) PageGetItem((Page) dp, lp);
	tuple->t_len = ItemIdGetLength(lp);
	tuple->t_tableOid = RelationGetRelid(relation);


	valid = HeapTupleSatisfiesVisibility(tuple, snapshot, buffer);

	LockBuffer(buffer, BUFFER_LOCK_UNLOCK);

	if (valid)
	{


		*userbuf = buffer;


		if (pgstat_info != NULL)
			pgstat_count_heap_fetch(pgstat_info);

		return true;
	}


	if (keep_buf)
		*userbuf = buffer;
	else
	{
		ReleaseBuffer(buffer);
		*userbuf = InvalidBuffer;
	}

	return false;
}
