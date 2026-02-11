isc_taskpool_destroy(isc_taskpool_t **poolp) {
	unsigned int i;
	isc_taskpool_t *pool = *poolp;
	for (i = 0; i < pool->ntasks; i++) {
		if (pool->tasks[i] != NULL)
			isc_task_detach(&pool->tasks[i]);
	}
	isc_mem_put(pool->mctx, pool->tasks,
		    pool->ntasks * sizeof(isc_task_t *));
	isc_mem_putanddetach(&pool->mctx, pool, sizeof(*pool));
	*poolp = NULL;
}
