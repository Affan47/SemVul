gfs_stat_cache_expiration_set(long lifespan_millsecond)
{
	struct timeval old_lifespan = stat_cache_lifespan;
	struct stat_cache_data *p;

	stat_cache_lifespan_is_set = 1;
	stat_cache_lifespan.tv_sec = lifespan_millsecond / 1000;
	stat_cache_lifespan.tv_usec =
	    (lifespan_millsecond - stat_cache_lifespan.tv_sec * 1000) * 1000;

	for (p = stat_cache_list_head.next; p != &stat_cache_list_head;
	    p = p->next) {
		gfarm_timeval_sub(&p->expiration, &old_lifespan);
		gfarm_timeval_add(&p->expiration, &stat_cache_lifespan);
	}
}
