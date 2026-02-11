arena_bin_lower_run(arena_t *arena, arena_chunk_t *chunk, arena_run_t *run,
    arena_bin_t *bin)
{


	if (bin->runcur == NULL)
		bin->runcur = run;
	else if ((uintptr_t)run < (uintptr_t)bin->runcur) {

		if (bin->runcur->nfree > 0) {
			arena_chunk_t *runcur_chunk =
			    CHUNK_ADDR2BASE(bin->runcur);
			size_t runcur_pageind = (((uintptr_t)bin->runcur -
			    (uintptr_t)runcur_chunk)) >> PAGE_SHIFT;
			arena_chunk_map_t *runcur_mapelm =
			    &runcur_chunk->map[runcur_pageind-map_bias];


			arena_run_tree_insert(&bin->runs, runcur_mapelm);
		}
		bin->runcur = run;
	} else {
		size_t run_pageind = (((uintptr_t)run -
		    (uintptr_t)chunk)) >> PAGE_SHIFT;
		arena_chunk_map_t *run_mapelm =
		    &chunk->map[run_pageind-map_bias];

		assert(arena_run_tree_search(&bin->runs, run_mapelm) == NULL);
		arena_run_tree_insert(&bin->runs, run_mapelm);
	}
}
