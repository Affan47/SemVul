ghes_estatus_cache_add(
	struct acpi_hest_generic *generic,
	struct acpi_hest_generic_status *estatus)
{
	int i, slot = -1, count;
	unsigned long long now, duration, period, max_period = 0;
	struct ghes_estatus_cache *cache, *slot_cache = NULL, *new_cache;

	new_cache = ghes_estatus_cache_alloc(generic, estatus);
	if (new_cache == NULL)
		return;
	rcu_read_lock();
	now = sched_clock();
	for (i = 0; i < GHES_ESTATUS_CACHES_SIZE; i++) {
		cache = rcu_dereference(ghes_estatus_caches[i]);
		if (cache == NULL) {
			slot = i;
			slot_cache = NULL;
			break;
		}
		duration = now - cache->time_in;
		if (duration >= GHES_ESTATUS_IN_CACHE_MAX_NSEC) {
			slot = i;
			slot_cache = cache;
			break;
		}
		count = atomic_read(&cache->count);
		period = duration;
		do_div(period, (count + 1));
		if (period > max_period) {
			max_period = period;
			slot = i;
			slot_cache = cache;
		}
	}

	smp_wmb();
	if (slot != -1 && cmpxchg(ghes_estatus_caches + slot,
				  slot_cache, new_cache) == slot_cache) {
		if (slot_cache)
			call_rcu(&slot_cache->rcu, ghes_estatus_cache_rcu_free);
	} else
		ghes_estatus_cache_free(new_cache);
	rcu_read_unlock();
}
