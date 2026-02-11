mark_cache_stats(struct cache_stat_collector *stats,
			     bool hit, bool bypass)
{
	if (!bypass)
		if (hit)
			atomic_inc(&stats->cache_hits);
		else
			atomic_inc(&stats->cache_misses);
	else
		if (hit)
			atomic_inc(&stats->cache_bypass_hits);
		else
			atomic_inc(&stats->cache_bypass_misses);
}
