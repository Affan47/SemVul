LogicalTapeBackspace(LogicalTapeSet *lts, int tapenum, size_t size)
{
	LogicalTape *lt;
	long		nblocks;
	int			newpos;

	Assert(tapenum >= 0 && tapenum < lts->nTapes);
	lt = &lts->tapes[tapenum];
	Assert(lt->frozen);


	if (size <= (size_t) lt->pos)
	{
		lt->pos -= (int) size;
		return true;
	}


	size -= (size_t) lt->pos;
	nblocks = size / BLCKSZ;
	size = size % BLCKSZ;
	if (size)
	{
		nblocks++;
		newpos = (int) (BLCKSZ - size);
	}
	else
		newpos = 0;
	if (nblocks > lt->curBlockNumber)
		return false;


	while (nblocks-- > 0)
	{
		long		datablocknum = ltsRecallPrevBlockNum(lts, lt->indirect);

		if (datablocknum == -1L)
			elog(ERROR, "unexpected end of tape");
		lt->curBlockNumber--;
		if (nblocks == 0)
		{
			ltsReadBlock(lts, datablocknum, (void *) lt->buffer);
			lt->nbytes = BLCKSZ;
		}
	}
	lt->pos = newpos;
	return true;
}
