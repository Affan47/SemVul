visibilitymap_truncate(Relation rel, BlockNumber nheapblocks)
{
	BlockNumber newnblocks;


	BlockNumber truncBlock = HEAPBLK_TO_MAPBLOCK(nheapblocks);
	uint32		truncByte = HEAPBLK_TO_MAPBYTE(nheapblocks);
	uint8		truncBit = HEAPBLK_TO_MAPBIT(nheapblocks);

#ifdef TRACE_VISIBILITYMAP
	elog(DEBUG1, "vm_truncate %s %d", RelationGetRelationName(rel), nheapblocks);
#endif

	RelationOpenSmgr(rel);


	if (!smgrexists(rel->rd_smgr, VISIBILITYMAP_FORKNUM))
		return;


	if (truncByte != 0 || truncBit != 0)
	{
		Buffer		mapBuffer;
		Page		page;
		char	   *map;

		newnblocks = truncBlock + 1;

		mapBuffer = vm_readbuf(rel, truncBlock, false);
		if (!BufferIsValid(mapBuffer))
		{

			return;
		}

		page = BufferGetPage(mapBuffer);
		map = PageGetContents(page);

		LockBuffer(mapBuffer, BUFFER_LOCK_EXCLUSIVE);


		MemSet(&map[truncByte + 1], 0, MAPSIZE - (truncByte + 1));


		map[truncByte] &= (1 << truncBit) - 1;

		MarkBufferDirty(mapBuffer);
		UnlockReleaseBuffer(mapBuffer);
	}
	else
		newnblocks = truncBlock;

	if (smgrnblocks(rel->rd_smgr, VISIBILITYMAP_FORKNUM) <= newnblocks)
	{

		return;
	}


	smgrtruncate(rel->rd_smgr, VISIBILITYMAP_FORKNUM, newnblocks);


	if (rel->rd_smgr)
		rel->rd_smgr->smgr_vm_nblocks = newnblocks;
}
