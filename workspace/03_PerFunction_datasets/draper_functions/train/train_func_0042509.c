tuplestore_set_eflags(Tuplestorestate *state, int eflags)
{
	int			i;

	if (state->status != TSS_INMEM || state->memtupcount != 0)
		elog(ERROR, "too late to call tuplestore_set_eflags");

	state->readptrs[0].eflags = eflags;
	for (i = 1; i < state->readptrcount; i++)
		eflags |= state->readptrs[i].eflags;
	state->eflags = eflags;
}
