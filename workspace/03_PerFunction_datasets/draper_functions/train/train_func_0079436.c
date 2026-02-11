gistgetbitmap(PG_FUNCTION_ARGS)
{
	IndexScanDesc scan = (IndexScanDesc) PG_GETARG_POINTER(0);
	TIDBitmap  *tbm = (TIDBitmap *) PG_GETARG_POINTER(1);
	GISTScanOpaque so = (GISTScanOpaque) scan->opaque;
	int64		ntids = 0;
	GISTSearchItem fakeItem;

	if (!so->qual_ok)
		PG_RETURN_INT64(0);

	pgstat_count_index_scan(scan->indexRelation);


	so->curTreeItem = NULL;
	so->curPageData = so->nPageData = 0;

	fakeItem.blkno = GIST_ROOT_BLKNO;
	memset(&fakeItem.data.parentlsn, 0, sizeof(GistNSN));
	gistScanPage(scan, &fakeItem, NULL, tbm, &ntids);


	for (;;)
	{
		GISTSearchItem *item = getNextGISTSearchItem(so);

		if (!item)
			break;

		CHECK_FOR_INTERRUPTS();

		gistScanPage(scan, item, so->curTreeItem->distances, tbm, &ntids);

		pfree(item);
	}

	PG_RETURN_INT64(ntids);
}
