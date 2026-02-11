dataIsMoveRight(GinBtree btree, Page page)
{
	ItemPointer iptr = GinDataPageGetRightBound(page);

	if (GinPageRightMost(page))
		return FALSE;

	return (compareItemPointers(btree->items + btree->curitem, iptr) > 0) ? TRUE : FALSE;
}
