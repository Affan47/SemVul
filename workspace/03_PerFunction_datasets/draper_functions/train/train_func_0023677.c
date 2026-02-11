puttuple_common(Tuplesortstate *state, SortTuple *tuple)
{
	switch (state->status)
	{
		case TSS_INITIAL:


			if (state->memtupcount >= state->memtupsize - 1)
			{
				(void) grow_memtuples(state);
				Assert(state->memtupcount < state->memtupsize);
			}
			state->memtuples[state->memtupcount++] = *tuple;


			if (state->bounded &&
				(state->memtupcount > state->bound * 2 ||
				 (state->memtupcount > state->bound && LACKMEM(state))))
			{
#ifdef TRACE_SORT
				if (trace_sort)
					elog(LOG, "switching to bounded heapsort at %d tuples: %s",
						 state->memtupcount,
						 pg_rusage_show(&state->ru_start));
#endif
				make_bounded_heap(state);
				return;
			}


			if (state->memtupcount < state->memtupsize && !LACKMEM(state))
				return;


			inittapes(state);


			dumptuples(state, false);
			break;

		case TSS_BOUNDED:


			if (COMPARETUP(state, tuple, &state->memtuples[0]) <= 0)
			{

				free_sort_tuple(state, tuple);
			}
			else
			{

				free_sort_tuple(state, &state->memtuples[0]);
				tuplesort_heap_siftup(state, false);
				tuplesort_heap_insert(state, tuple, 0, false);
			}
			break;

		case TSS_BUILDRUNS:


			Assert(state->memtupcount > 0);
			if (COMPARETUP(state, tuple, &state->memtuples[0]) >= 0)
				tuplesort_heap_insert(state, tuple, state->currentRun, true);
			else
				tuplesort_heap_insert(state, tuple, state->currentRun + 1, true);


			dumptuples(state, false);
			break;

		default:
			elog(ERROR, "invalid tuplesort state");
			break;
	}
}
