ginFindLeafPage(GinBtree btree, GinBtreeStack *stack)
{
	bool		isfirst = TRUE;
	BlockNumber rootBlkno;

	if (!stack)
		stack = ginPrepareFindLeafPage(btree, GIN_ROOT_BLKNO);
	rootBlkno = stack->blkno;

	for (;;)
	{
		Page		page;
		BlockNumber child;
		int			access = GIN_SHARE;

		stack->off = InvalidOffsetNumber;

		page = BufferGetPage(stack->buffer);

		if (isfirst)
		{
			if (GinPageIsLeaf(page) && !btree->searchMode)
				access = GIN_EXCLUSIVE;
			isfirst = FALSE;
		}
		else
			access = ginTraverseLock(stack->buffer, btree->searchMode);


		while (btree->fullScan == FALSE && stack->blkno != rootBlkno && btree->isMoveRight(btree, page))
		{
			BlockNumber rightlink = GinPageGetOpaque(page)->rightlink;

			if (rightlink == InvalidBlockNumber)

				break;

			stack->blkno = rightlink;
			LockBuffer(stack->buffer, GIN_UNLOCK);
			stack->buffer = ReleaseAndReadBuffer(stack->buffer, btree->index, stack->blkno);
			LockBuffer(stack->buffer, access);
			page = BufferGetPage(stack->buffer);
		}

		if (GinPageIsLeaf(page))
			return stack;


		child = btree->findChildPage(btree, stack);

		LockBuffer(stack->buffer, GIN_UNLOCK);
		Assert(child != InvalidBlockNumber);
		Assert(stack->blkno != child);

		if (btree->searchMode)
		{

			stack->blkno = child;
			stack->buffer = ReleaseAndReadBuffer(stack->buffer, btree->index, stack->blkno);
		}
		else
		{
			GinBtreeStack *ptr = (GinBtreeStack *) palloc(sizeof(GinBtreeStack));

			ptr->parent = stack;
			stack = ptr;
			stack->blkno = child;
			stack->buffer = ReadBuffer(btree->index, stack->blkno);
			stack->predictNumber = 1;
		}
	}


	return NULL;
}
