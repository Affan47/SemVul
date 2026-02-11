make_bounded_heap(Tuplesortstate *state)
{
	int			tupcount = state->memtupcount;
	int			i;

	Assert(state->status == TSS_INITIAL);
	Assert(state->bounded);
	Assert(tupcount >= state->bound);


	reversedirection(state);

	state->memtupcount = 0;
	for (i = 0; i < tupcount; i++)
	{
		if (state->memtupcount >= state->bound &&
		  COMPARETUP(state, &state->memtuples[i], &state->memtuples[0]) <= 0)
		{

			free_sort_tuple(state, &state->memtuples[i]);
			CHECK_FOR_INTERRUPTS();
		}
		else
		{


			SortTuple	stup = state->memtuples[i];

			tuplesort_heap_insert(state, &stup, 0, false);


			if (state->memtupcount > state->bound)
			{
				free_sort_tuple(state, &state->memtuples[0]);
				tuplesort_heap_siftup(state, false);
			}
		}
	}

	Assert(state->memtupcount == state->bound);
	state->status = TSS_BOUNDED;
}
