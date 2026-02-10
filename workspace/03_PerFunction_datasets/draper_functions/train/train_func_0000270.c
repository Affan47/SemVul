vacuum_heap(VRelStats *vacrelstats, Relation onerel, VacPageList vacuum_pages)
{
	Buffer		buf;
	VacPage    *vacpage;
	BlockNumber relblocks;
	int			nblocks;
	int			i;

	nblocks = vacuum_pages->num_pages;
	nblocks -= vacuum_pages->empty_end_pages;

	for (i = 0, vacpage = vacuum_pages->pagedesc; i < nblocks; i++, vacpage++)
	{
		vacuum_delay_point();

		if ((*vacpage)->offsets_free > 0)
		{
			buf = ReadBufferExtended(onerel, MAIN_FORKNUM, (*vacpage)->blkno,
									 RBM_NORMAL, vac_strategy);
			LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
			vacuum_page(onerel, buf, *vacpage);
			UnlockReleaseBuffer(buf);
		}
	}


	Assert(vacrelstats->rel_pages >= vacuum_pages->empty_end_pages);
	if (vacuum_pages->empty_end_pages > 0)
	{
		relblocks = vacrelstats->rel_pages - vacuum_pages->empty_end_pages;
		ereport(elevel,
				(errmsg("\"%s\": truncated %u to %u pages",
						RelationGetRelationName(onerel),
						vacrelstats->rel_pages, relblocks)));
		RelationTruncate(onerel, relblocks);


		CacheInvalidateRelcache(onerel);

		vacrelstats->rel_pages = relblocks;
	}
}
