FreeSpaceMapTruncateRel(Relation rel, BlockNumber nblocks)
{
	BlockNumber new_nfsmblocks;
	FSMAddress	first_removed_address;
	uint16		first_removed_slot;
	Buffer		buf;

	RelationOpenSmgr(rel);


	if (!smgrexists(rel->rd_smgr, FSM_FORKNUM))
		return;


	first_removed_address = fsm_get_location(nblocks, &first_removed_slot);


	if (first_removed_slot > 0)
	{
		buf = fsm_readbuf(rel, first_removed_address, false);
		if (!BufferIsValid(buf))
			return;
		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
		fsm_truncate_avail(BufferGetPage(buf), first_removed_slot);
		MarkBufferDirtyHint(buf, false);
		UnlockReleaseBuffer(buf);

		new_nfsmblocks = fsm_logical_to_physical(first_removed_address) + 1;
	}
	else
	{
		new_nfsmblocks = fsm_logical_to_physical(first_removed_address);
		if (smgrnblocks(rel->rd_smgr, FSM_FORKNUM) <= new_nfsmblocks)
			return;
	}


	smgrtruncate(rel->rd_smgr, FSM_FORKNUM, new_nfsmblocks);


	if (rel->rd_smgr)
		rel->rd_smgr->smgr_fsm_nblocks = new_nfsmblocks;
}
