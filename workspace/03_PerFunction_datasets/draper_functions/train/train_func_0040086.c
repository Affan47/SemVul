resetSpGistScanOpaque(SpGistScanOpaque so)
{
	ScanStackEntry *startEntry;

	freeScanStack(so);

	if (so->searchNulls)
	{

		startEntry = (ScanStackEntry *) palloc0(sizeof(ScanStackEntry));
		ItemPointerSet(&startEntry->ptr, SPGIST_NULL_BLKNO, FirstOffsetNumber);
		so->scanStack = lappend(so->scanStack, startEntry);
	}

	if (so->searchNonNulls)
	{

		startEntry = (ScanStackEntry *) palloc0(sizeof(ScanStackEntry));
		ItemPointerSet(&startEntry->ptr, SPGIST_ROOT_BLKNO, FirstOffsetNumber);
		so->scanStack = lappend(so->scanStack, startEntry);
	}

	if (so->want_itup)
	{

		int			i;

		for (i = 0; i < so->nPtrs; i++)
			pfree(so->indexTups[i]);
	}
	so->iPtr = so->nPtrs = 0;
}
