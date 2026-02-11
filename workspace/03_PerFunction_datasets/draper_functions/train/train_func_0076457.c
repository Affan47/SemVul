arena_purge(arena_t *arena, bool all)
{
	arena_chunk_t *chunk;
	size_t npurgatory;
	if (config_debug) {
		size_t ndirty = 0;

		ql_foreach(chunk, &arena->chunks_dirty, link_dirty) {
		    assert(chunk->dirtied);
		    ndirty += chunk->ndirty;
		}
		assert(ndirty == arena->ndirty);
	}
	assert(arena->ndirty > arena->npurgatory || all);
	assert(arena->ndirty - arena->npurgatory > chunk_npages || all);
	assert((arena->nactive >> opt_lg_dirty_mult) < (arena->ndirty -
	    arena->npurgatory) || all);

	if (config_stats)
		arena->stats.npurge++;


	npurgatory = arena->ndirty - arena->npurgatory;
	if (all == false) {
		assert(npurgatory >= arena->nactive >> opt_lg_dirty_mult);
		npurgatory -= arena->nactive >> opt_lg_dirty_mult;
	}
	arena->npurgatory += npurgatory;

	while (npurgatory > 0) {

		chunk = ql_first(&arena->chunks_dirty);
		if (chunk == NULL) {


			arena->npurgatory -= npurgatory;
			return;
		}
		while (chunk->ndirty == 0) {
			ql_remove(&arena->chunks_dirty, chunk, link_dirty);
			chunk->dirtied = false;
			chunk = ql_first(&arena->chunks_dirty);
			if (chunk == NULL) {

				arena->npurgatory -= npurgatory;
				return;
			}
		}

		if (chunk->ndirty > npurgatory) {


			arena->npurgatory += chunk->ndirty - npurgatory;
			npurgatory = chunk->ndirty;
		}

		arena->npurgatory -= chunk->ndirty;
		npurgatory -= chunk->ndirty;
		arena_chunk_purge(arena, chunk);
	}
}
