tuplestore_end(Tuplestorestate *state)
{
	int			i;

	if (state->myfile)
		BufFileClose(state->myfile);
	if (state->memtuples)
	{
		for (i = state->memtupdeleted; i < state->memtupcount; i++)
			pfree(state->memtuples[i]);
		pfree(state->memtuples);
	}
	pfree(state->readptrs);
	pfree(state);
}
