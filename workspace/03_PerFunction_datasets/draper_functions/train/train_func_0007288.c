readtup_index(Tuplesortstate *state, SortTuple *stup,
			  int tapenum, unsigned int len)
{
	unsigned int tuplen = len - sizeof(unsigned int);
	IndexTuple	tuple = (IndexTuple) palloc(tuplen);

	USEMEM(state, GetMemoryChunkSpace(tuple));
	if (LogicalTapeRead(state->tapeset, tapenum, (void *) tuple,
						tuplen) != tuplen)
		elog(ERROR, "unexpected end of data");
	if (state->randomAccess)
		if (LogicalTapeRead(state->tapeset, tapenum, (void *) &tuplen,
							sizeof(tuplen)) != sizeof(tuplen))
			elog(ERROR, "unexpected end of data");
	stup->tuple = (void *) tuple;

	stup->datum1 = index_getattr(tuple,
								 1,
								 RelationGetDescr(state->indexRel),
								 &stup->isnull1);
}
