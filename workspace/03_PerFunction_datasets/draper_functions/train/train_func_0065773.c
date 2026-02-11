ginEntryInsert(Relation index, GinState *ginstate,
			   OffsetNumber attnum, Datum value,
			   ItemPointerData *items, uint32 nitem,
			   GinStatsData *buildStats)
{
	GinBtreeData btree;
	GinBtreeStack *stack;
	IndexTuple	itup;
	Page		page;


	if (buildStats)
		buildStats->nEntries++;

	ginPrepareEntryScan(&btree, index, attnum, value, ginstate);

	stack = ginFindLeafPage(&btree, NULL);
	page = BufferGetPage(stack->buffer);

	if (btree.findItem(&btree, stack))
	{

		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stack->off));

		if (GinIsPostingTree(itup))
		{

			GinPostingTreeScan *gdi;
			BlockNumber rootPostingTree = GinGetPostingTree(itup);


			LockBuffer(stack->buffer, GIN_UNLOCK);
			freeGinBtreeStack(stack);


			gdi = ginPrepareScanPostingTree(index, rootPostingTree, FALSE);
			gdi->btree.isBuild = (buildStats != NULL);
			ginInsertItemPointer(gdi, items, nitem, buildStats);
			pfree(gdi);

			return;
		}

		itup = addItemPointersToTuple(index, ginstate, stack, itup,
									  items, nitem, buildStats);

		btree.isDelete = TRUE;
	}
	else
	{

		itup = GinFormTuple(index, ginstate, attnum, value, items, 1, true);

		if (nitem > 1)
		{

			IndexTuple	previtup = itup;

			itup = addItemPointersToTuple(index, ginstate, stack, previtup,
										  items + 1, nitem - 1, buildStats);
			pfree(previtup);
		}
	}

	btree.entry = itup;
	ginInsertValue(&btree, stack, buildStats);
	pfree(itup);
}
