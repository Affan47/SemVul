__perform_reclaim(gfp_t gfp_mask, unsigned int order,
					const struct alloc_context *ac)
{
	struct reclaim_state reclaim_state;
	int progress;

	cond_resched();


	cpuset_memory_pressure_bump();
	current->flags |= PF_MEMALLOC;
	lockdep_set_current_reclaim_state(gfp_mask);
	reclaim_state.reclaimed_slab = 0;
	current->reclaim_state = &reclaim_state;

	progress = try_to_free_pages(ac->zonelist, order, gfp_mask,
								ac->nodemask);

	current->reclaim_state = NULL;
	lockdep_clear_current_reclaim_state();
	current->flags &= ~PF_MEMALLOC;

	cond_resched();

	return progress;
}
