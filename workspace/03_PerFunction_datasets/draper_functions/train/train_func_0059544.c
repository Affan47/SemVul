ReorderBufferIterTXNInit(ReorderBuffer *rb, ReorderBufferTXN *txn)
{
	Size		nr_txns = 0;
	ReorderBufferIterTXNState *state;
	dlist_iter	cur_txn_i;
	int32		off;


	if (txn->nentries > 0)
		nr_txns++;

	dlist_foreach(cur_txn_i, &txn->subtxns)
	{
		ReorderBufferTXN *cur_txn;

		cur_txn = dlist_container(ReorderBufferTXN, node, cur_txn_i.cur);

		if (cur_txn->nentries > 0)
			nr_txns++;
	}


	state = (ReorderBufferIterTXNState *)
		MemoryContextAllocZero(rb->context,
							   sizeof(ReorderBufferIterTXNState) +
							   sizeof(ReorderBufferIterTXNEntry) * nr_txns);

	state->nr_txns = nr_txns;
	dlist_init(&state->old_change);

	for (off = 0; off < state->nr_txns; off++)
	{
		state->entries[off].fd = -1;
		state->entries[off].segno = 0;
	}


	state->heap = binaryheap_allocate(state->nr_txns,
									  ReorderBufferIterCompare,
									  state);


	off = 0;


	if (txn->nentries > 0)
	{
		ReorderBufferChange *cur_change;

		if (txn->nentries != txn->nentries_mem)
			ReorderBufferRestoreChanges(rb, txn, &state->entries[off].fd,
										&state->entries[off].segno);

		cur_change = dlist_head_element(ReorderBufferChange, node,
										&txn->changes);

		state->entries[off].lsn = cur_change->lsn;
		state->entries[off].change = cur_change;
		state->entries[off].txn = txn;

		binaryheap_add_unordered(state->heap, Int32GetDatum(off++));
	}


	dlist_foreach(cur_txn_i, &txn->subtxns)
	{
		ReorderBufferTXN *cur_txn;

		cur_txn = dlist_container(ReorderBufferTXN, node, cur_txn_i.cur);

		if (cur_txn->nentries > 0)
		{
			ReorderBufferChange *cur_change;

			if (txn->nentries != txn->nentries_mem)
				ReorderBufferRestoreChanges(rb, cur_txn,
											&state->entries[off].fd,
											&state->entries[off].segno);

			cur_change = dlist_head_element(ReorderBufferChange, node,
											&cur_txn->changes);

			state->entries[off].lsn = cur_change->lsn;
			state->entries[off].change = cur_change;
			state->entries[off].txn = cur_txn;

			binaryheap_add_unordered(state->heap, Int32GetDatum(off++));
		}
	}


	binaryheap_build(state->heap);

	return state;
}
