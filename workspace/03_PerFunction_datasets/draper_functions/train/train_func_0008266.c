_bt_leafbuild(BTSpool *btspool, BTSpool *btspool2)
{
	BTWriteState wstate;

#ifdef BTREE_BUILD_STATS
	if (log_btree_build_stats)
	{
		ShowUsage("BTREE BUILD (Spool) STATISTICS");
		ResetUsage();
	}
#endif

	tuplesort_performsort(btspool->sortstate);
	if (btspool2)
		tuplesort_performsort(btspool2->sortstate);

	wstate.index = btspool->index;


	wstate.btws_use_wal = XLogIsNeeded() && RelationNeedsWAL(wstate.index);


	wstate.btws_pages_alloced = BTREE_METAPAGE + 1;
	wstate.btws_pages_written = 0;
	wstate.btws_zeropage = NULL;

	_bt_load(&wstate, btspool, btspool2);
}
