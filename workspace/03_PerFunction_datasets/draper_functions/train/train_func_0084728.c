search_idle_count(struct search_idle_state *s,
	struct search_idle_host_state *h,
	int *usable_numberp, int *idle_numberp, int *semi_idle_numberp)
{
	float loadavg = h->loadavg;
	int ncpu = h->ncpu;
	int ok = 1;

	if (s->write_mode &&
	    (h->flags & HOST_STATE_FLAG_STATFS_AVAIL) != 0 &&
	    h->diskavail < gfarm_minimum_free_disk_space)
		ok = 0;
	if (ok)
		(*usable_numberp)++;

	if (ncpu <= 0)
		ncpu = 1;
	loadavg += h->scheduled * VIRTUAL_LOAD_FOR_SCHEDULED_HOST;
	if (ok && loadavg / ncpu <= IDLE_LOAD_AVERAGE)
		(*idle_numberp)++;


	if (ok && loadavg <= SEMI_IDLE_LOAD_AVERAGE)
		(*semi_idle_numberp)++;
}
