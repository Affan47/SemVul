mergeprereadone(Tuplesortstate *state, int srcTape)
{
	unsigned int tuplen;
	SortTuple	stup;
	int			tupIndex;
	long		priorAvail,
				spaceUsed;

	if (!state->mergeactive[srcTape])
		return;
	priorAvail = state->availMem;
	state->availMem = state->mergeavailmem[srcTape];
	while ((state->mergeavailslots[srcTape] > 0 && !LACKMEM(state)) ||
		   state->mergenext[srcTape] == 0)
	{

		if ((tuplen = getlen(state, srcTape, true)) == 0)
		{
			state->mergeactive[srcTape] = false;
			break;
		}
		READTUP(state, &stup, srcTape, tuplen);

		tupIndex = state->mergefreelist;
		if (tupIndex)
			state->mergefreelist = state->memtuples[tupIndex].tupindex;
		else
		{
			tupIndex = state->mergefirstfree++;
			Assert(tupIndex < state->memtupsize);
		}
		state->mergeavailslots[srcTape]--;

		stup.tupindex = 0;
		state->memtuples[tupIndex] = stup;
		if (state->mergelast[srcTape])
			state->memtuples[state->mergelast[srcTape]].tupindex = tupIndex;
		else
			state->mergenext[srcTape] = tupIndex;
		state->mergelast[srcTape] = tupIndex;
	}

	spaceUsed = state->mergeavailmem[srcTape] - state->availMem;
	state->mergeavailmem[srcTape] = state->availMem;
	state->availMem = priorAvail - spaceUsed;
}
