ctl_arena_stats_amerge(ctl_arena_stats_t *cstats, arena_t *arena)
{
	unsigned i;

	arena_stats_merge(arena, &cstats->dss, &cstats->pactive,
	    &cstats->pdirty, &cstats->astats, cstats->bstats, cstats->lstats);

	for (i = 0; i < NBINS; i++) {
		cstats->allocated_small += cstats->bstats[i].allocated;
		cstats->nmalloc_small += cstats->bstats[i].nmalloc;
		cstats->ndalloc_small += cstats->bstats[i].ndalloc;
		cstats->nrequests_small += cstats->bstats[i].nrequests;
	}
}
