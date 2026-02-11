addItemPointersToTuple(Relation index, GinState *ginstate, GinBtreeStack *stack,
		  IndexTuple old, ItemPointerData *items, uint32 nitem, bool isBuild)
{
	bool		isnull;
	Datum		key = index_getattr(old, FirstOffsetNumber, ginstate->tupdesc, &isnull);
	IndexTuple	res = GinFormTuple(ginstate, key, NULL, nitem + GinGetNPosting(old));

	if (res)
	{

		MergeItemPointers(GinGetPosting(res),
						  GinGetPosting(old), GinGetNPosting(old),
						  items, nitem
			);

		GinSetNPosting(res, nitem + GinGetNPosting(old));
	}
	else
	{
		BlockNumber postingRoot;
		GinPostingTreeScan *gdi;


		res = GinFormTuple(ginstate, key, NULL, 0);
		postingRoot = createPostingTree(index, GinGetPosting(old), GinGetNPosting(old));
		GinSetPostingTree(res, postingRoot);

		gdi = prepareScanPostingTree(index, postingRoot, FALSE);
		gdi->btree.isBuild = isBuild;

		insertItemPointer(gdi, items, nitem);

		pfree(gdi);
	}

	return res;
}
