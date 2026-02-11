arena_purge(arena_t *arena, bool all)
{
	arena_chunk_t *chunk;
	size_t npurgatory;
	if (config_debug) {
		size_t ndirty = 0;

		arena_chunk_dirty_iter(&arena->chunks_dirty, NULL,
		    chunks_dirty_iter_cb, (void *)&ndirty);
		assert(ndirty == arena->ndirty);
	}
	assert(arena->ndirty > arena->npurgatory || all);
	assert((arena->nactive >> opt_lg_dirty_mult) < (arena->ndirty -
	    arena->npurgatory) || all);

	if (config_stats)
		arena->stats.npurge++;


	{
		size_t npurgeable = arena->ndirty - arena->npurgatory;

		if (all == false) {
			size_t threshold = (arena->nactive >>
			    opt_lg_dirty_mult);

			npurgatory = npurgeable - threshold;
		} else
			npurgatory = npurgeable;
	}
	arena->npurgatory += npurgatory;

	while (npurgatory > 0) {
		size_t npurgeable, npurged, nunpurged;


		chunk = arena_chunk_dirty_first(&arena->chunks_dirty);
		if (chunk == NULL) {


			arena->npurgatory -= npurgatory;
			return;
		}
		npurgeable = chunk->ndirty;
		assert(npurgeable != 0);

		if (npurgeable > npurgatory && chunk->nruns_adjac == 0) {


			arena->npurgatory += npurgeable - npurgatory;
			npurgatory = npurgeable;
		}


		arena->npurgatory -= npurgeable;
		npurgatory -= npurgeable;
		npurged = arena_chunk_purge(arena, chunk, all);
		nunpurged = npurgeable - npurged;
		arena->npurgatory += nunpurged;
		npurgatory += nunpurged;
	}
}
