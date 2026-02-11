spgFormDeadTuple(SpGistState *state, int tupstate,
				 BlockNumber blkno, OffsetNumber offnum)
{
	SpGistDeadTuple tuple = (SpGistDeadTuple) state->deadTupleStorage;

	tuple->tupstate = tupstate;
	tuple->size = SGDTSIZE;
	tuple->nextOffset = InvalidOffsetNumber;

	if (tupstate == SPGIST_REDIRECT)
	{
		ItemPointerSet(&tuple->pointer, blkno, offnum);
		Assert(TransactionIdIsValid(state->myXid));
		tuple->xid = state->myXid;
	}
	else
	{
		ItemPointerSetInvalid(&tuple->pointer);
		tuple->xid = InvalidTransactionId;
	}

	return tuple;
}
