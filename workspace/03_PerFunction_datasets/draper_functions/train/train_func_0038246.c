raw_heap_insert(RewriteState state, HeapTuple tup)
{
	Page		page = state->rs_buffer;
	Size		pageFreeSpace,
				saveFreeSpace;
	Size		len;
	OffsetNumber newoff;
	HeapTuple	heaptup;


	if (state->rs_new_rel->rd_rel->relkind == RELKIND_TOASTVALUE)
	{

		Assert(!HeapTupleHasExternal(tup));
		heaptup = tup;
	}
	else if (HeapTupleHasExternal(tup) || tup->t_len > TOAST_TUPLE_THRESHOLD)
		heaptup = toast_insert_or_update(state->rs_new_rel, tup, NULL,
										 HEAP_INSERT_SKIP_FSM |
										 (state->rs_use_wal ?
										  0 : HEAP_INSERT_SKIP_WAL));
	else
		heaptup = tup;

	len = MAXALIGN(heaptup->t_len);


	if (len > MaxHeapTupleSize)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("row is too big: size %lu, maximum size %lu",
						(unsigned long) len,
						(unsigned long) MaxHeapTupleSize)));


	saveFreeSpace = RelationGetTargetPageFreeSpace(state->rs_new_rel,
												   HEAP_DEFAULT_FILLFACTOR);


	if (state->rs_buffer_valid)
	{
		pageFreeSpace = PageGetHeapFreeSpace(page);

		if (len + saveFreeSpace > pageFreeSpace)
		{


			if (state->rs_use_wal)
				log_newpage(&state->rs_new_rel->rd_node,
							MAIN_FORKNUM,
							state->rs_blockno,
							page);


			RelationOpenSmgr(state->rs_new_rel);
			smgrextend(state->rs_new_rel->rd_smgr, MAIN_FORKNUM,
					   state->rs_blockno, (char *) page, true);

			state->rs_blockno++;
			state->rs_buffer_valid = false;
		}
	}

	if (!state->rs_buffer_valid)
	{

		PageInit(page, BLCKSZ, 0);
		state->rs_buffer_valid = true;
	}


	newoff = PageAddItem(page, (Item) heaptup->t_data, heaptup->t_len,
						 InvalidOffsetNumber, false, true);
	if (newoff == InvalidOffsetNumber)
		elog(ERROR, "failed to add tuple");


	ItemPointerSet(&(tup->t_self), state->rs_blockno, newoff);


	if (!ItemPointerIsValid(&tup->t_data->t_ctid))
	{
		ItemId		newitemid;
		HeapTupleHeader onpage_tup;

		newitemid = PageGetItemId(page, newoff);
		onpage_tup = (HeapTupleHeader) PageGetItem(page, newitemid);

		onpage_tup->t_ctid = tup->t_self;
	}


	if (heaptup != tup)
		heap_freetuple(heaptup);
}
