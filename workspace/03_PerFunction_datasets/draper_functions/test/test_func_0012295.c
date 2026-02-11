ginScanToDelete(GinVacuumState *gvs, BlockNumber blkno, bool isRoot, DataPageDeleteStack *parent, OffsetNumber myoff)
{
	DataPageDeleteStack *me;
	Buffer		buffer;
	Page		page;
	bool		meDelete = FALSE;

	if (isRoot)
	{
		me = parent;
	}
	else
	{
		if (!parent->child)
		{
			me = (DataPageDeleteStack *) palloc0(sizeof(DataPageDeleteStack));
			me->parent = parent;
			parent->child = me;
			me->leftBlkno = InvalidBlockNumber;
		}
		else
			me = parent->child;
	}

	buffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, blkno,
								RBM_NORMAL, gvs->strategy);
	page = BufferGetPage(buffer);

	Assert(GinPageIsData(page));

	if (!GinPageIsLeaf(page))
	{
		OffsetNumber i;

		me->blkno = blkno;
		for (i = FirstOffsetNumber; i <= GinPageGetOpaque(page)->maxoff; i++)
		{
			PostingItem *pitem = (PostingItem *) GinDataPageGetItem(page, i);

			if (ginScanToDelete(gvs, PostingItemGetBlockNumber(pitem), FALSE, me, i))
				i--;
		}
	}

	if (GinPageGetOpaque(page)->maxoff < FirstOffsetNumber)
	{
		if (!(me->leftBlkno == InvalidBlockNumber && GinPageRightMost(page)))
		{

			Assert(!isRoot);
			if (GinPageGetOpaque(page)->maxoff < FirstOffsetNumber)
			{
				ginDeletePage(gvs, blkno, me->leftBlkno, me->parent->blkno, myoff, me->parent->isRoot);
				meDelete = TRUE;
			}
		}
	}

	ReleaseBuffer(buffer);

	if (!meDelete)
		me->leftBlkno = blkno;

	return meDelete;
}
