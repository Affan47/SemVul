ginvacuumcleanup(PG_FUNCTION_ARGS)
{
	IndexVacuumInfo *info = (IndexVacuumInfo *) PG_GETARG_POINTER(0);
	IndexBulkDeleteResult *stats = (IndexBulkDeleteResult *) PG_GETARG_POINTER(1);
	Relation	index = info->index;
	bool		needLock;
	BlockNumber npages,
				blkno;
	BlockNumber totFreePages,
				nFreePages,
			   *freePages,
				maxFreePages;
	BlockNumber lastBlock = GIN_ROOT_BLKNO,
				lastFilledBlock = GIN_ROOT_BLKNO;


	if (stats == NULL)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));


	stats->num_index_tuples = info->num_heap_tuples;


	if (info->vacuum_full)
		needLock = false;
	else
		needLock = !RELATION_IS_LOCAL(index);

	if (needLock)
		LockRelationForExtension(index, ExclusiveLock);
	npages = RelationGetNumberOfBlocks(index);
	if (needLock)
		UnlockRelationForExtension(index, ExclusiveLock);

	maxFreePages = npages;
	if (maxFreePages > MaxFSMPages)
		maxFreePages = MaxFSMPages;

	totFreePages = nFreePages = 0;
	freePages = (BlockNumber *) palloc(sizeof(BlockNumber) * maxFreePages);

	for (blkno = GIN_ROOT_BLKNO + 1; blkno < npages; blkno++)
	{
		Buffer		buffer;
		Page		page;

		vacuum_delay_point();

		buffer = ReadBufferWithStrategy(index, blkno, info->strategy);
		LockBuffer(buffer, GIN_SHARE);
		page = (Page) BufferGetPage(buffer);

		if (GinPageIsDeleted(page))
		{
			if (nFreePages < maxFreePages)
				freePages[nFreePages++] = blkno;
			totFreePages++;
		}
		else
			lastFilledBlock = blkno;

		UnlockReleaseBuffer(buffer);
	}
	lastBlock = npages - 1;

	if (info->vacuum_full && nFreePages > 0)
	{

		int			i;

		for (i = 0; i < nFreePages; i++)
			if (freePages[i] >= lastFilledBlock)
			{
				totFreePages = nFreePages = i;
				break;
			}

		if (lastBlock > lastFilledBlock)
			RelationTruncate(index, lastFilledBlock + 1);

		stats->pages_removed = lastBlock - lastFilledBlock;
	}

	RecordIndexFreeSpace(&index->rd_node, totFreePages, nFreePages, freePages);
	stats->pages_free = totFreePages;

	if (needLock)
		LockRelationForExtension(index, ExclusiveLock);
	stats->num_pages = RelationGetNumberOfBlocks(index);
	if (needLock)
		UnlockRelationForExtension(index, ExclusiveLock);

	PG_RETURN_POINTER(stats);
}
