RememberFsyncRequest(RelFileNode rnode, ForkNumber forknum, BlockNumber segno)
{
	Assert(pendingOpsTable);

	if (segno == FORGET_RELATION_FSYNC)
	{

		PendingOperationEntry *entry;

		entry = (PendingOperationEntry *) hash_search(pendingOpsTable,
													  &rnode,
													  HASH_FIND,
													  NULL);
		if (entry)
		{


			if (forknum == InvalidForkNumber)
			{

				for (forknum = 0; forknum <= MAX_FORKNUM; forknum++)
				{
					bms_free(entry->requests[forknum]);
					entry->requests[forknum] = NULL;
					entry->canceled[forknum] = true;
				}
			}
			else
			{

				bms_free(entry->requests[forknum]);
				entry->requests[forknum] = NULL;
				entry->canceled[forknum] = true;
			}
		}
	}
	else if (segno == FORGET_DATABASE_FSYNC)
	{

		HASH_SEQ_STATUS hstat;
		PendingOperationEntry *entry;
		ListCell   *cell,
				   *prev,
				   *next;


		hash_seq_init(&hstat, pendingOpsTable);
		while ((entry = (PendingOperationEntry *) hash_seq_search(&hstat)) != NULL)
		{
			if (entry->rnode.dbNode == rnode.dbNode)
			{

				for (forknum = 0; forknum <= MAX_FORKNUM; forknum++)
				{
					bms_free(entry->requests[forknum]);
					entry->requests[forknum] = NULL;
					entry->canceled[forknum] = true;
				}
			}
		}


		prev = NULL;
		for (cell = list_head(pendingUnlinks); cell; cell = next)
		{
			PendingUnlinkEntry *entry = (PendingUnlinkEntry *) lfirst(cell);

			next = lnext(cell);
			if (entry->rnode.dbNode == rnode.dbNode)
			{
				pendingUnlinks = list_delete_cell(pendingUnlinks, cell, prev);
				pfree(entry);
			}
			else
				prev = cell;
		}
	}
	else if (segno == UNLINK_RELATION_REQUEST)
	{

		MemoryContext oldcxt = MemoryContextSwitchTo(pendingOpsCxt);
		PendingUnlinkEntry *entry;


		Assert(forknum == MAIN_FORKNUM);

		entry = palloc(sizeof(PendingUnlinkEntry));
		entry->rnode = rnode;
		entry->cycle_ctr = mdckpt_cycle_ctr;

		pendingUnlinks = lappend(pendingUnlinks, entry);

		MemoryContextSwitchTo(oldcxt);
	}
	else
	{

		MemoryContext oldcxt = MemoryContextSwitchTo(pendingOpsCxt);
		PendingOperationEntry *entry;
		bool		found;

		entry = (PendingOperationEntry *) hash_search(pendingOpsTable,
													  &rnode,
													  HASH_ENTER,
													  &found);

		if (!found)
		{
			entry->cycle_ctr = mdsync_cycle_ctr;
			MemSet(entry->requests, 0, sizeof(entry->requests));
			MemSet(entry->canceled, 0, sizeof(entry->canceled));
		}


		entry->requests[forknum] = bms_add_member(entry->requests[forknum],
												  (int) segno);

		MemoryContextSwitchTo(oldcxt);
	}
}
