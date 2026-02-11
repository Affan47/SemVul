copyIndexTuple(IndexTuple itup, Page page)
{
	IndexTuple	nitup;

	if (GinPageIsLeaf(page) && !GinIsPostingTree(itup))
	{
		nitup = (IndexTuple) palloc(MAXALIGN(GinGetOrigSizePosting(itup)));
		memcpy(nitup, itup, GinGetOrigSizePosting(itup));
		nitup->t_info &= ~INDEX_SIZE_MASK;
		nitup->t_info |= GinGetOrigSizePosting(itup);
	}
	else
	{
		nitup = (IndexTuple) palloc(MAXALIGN(IndexTupleSize(itup)));
		memcpy(nitup, itup, IndexTupleSize(itup));
	}

	return nitup;
}
