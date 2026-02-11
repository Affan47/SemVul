moveRightIfItNeeded(GinBtreeData *btree, GinBtreeStack *stack)
{
	Page		page = BufferGetPage(stack->buffer);

	if (stack->off > PageGetMaxOffsetNumber(page))
	{


		if (GinPageRightMost(page))
			return false;

		stack->buffer = ginStepRight(stack->buffer, btree->index, GIN_SHARE);
		stack->blkno = BufferGetBlockNumber(stack->buffer);
		stack->off = FirstOffsetNumber;
	}

	return true;
}
