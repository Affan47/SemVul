comparetup_datum(const SortTuple *a, const SortTuple *b, Tuplesortstate *state)
{

	CHECK_FOR_INTERRUPTS();

	return inlineApplySortFunction(&state->sortOpFn, state->sortFnFlags,
								   state->sortCollation,
								   a->datum1, a->isnull1,
								   b->datum1, b->isnull1);
}
