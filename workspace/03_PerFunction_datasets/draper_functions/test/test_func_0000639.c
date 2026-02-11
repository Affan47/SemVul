dm_stats_cleanup(struct dm_stats *stats)
{
	size_t ni;
	struct dm_stat *s;
	struct dm_stat_shared *shared;

	while (!list_empty(&stats->list)) {
		s = container_of(stats->list.next, struct dm_stat, list_entry);
		list_del(&s->list_entry);
		for (ni = 0; ni < s->n_entries; ni++) {
			shared = &s->stat_shared[ni];
			if (WARN_ON(dm_stat_in_flight(shared))) {
				DMCRIT("leaked in-flight counter at index %lu "
				       "(start %llu, end %llu, step %llu): reads %d, writes %d",
				       (unsigned long)ni,
				       (unsigned long long)s->start,
				       (unsigned long long)s->end,
				       (unsigned long long)s->step,
				       atomic_read(&shared->in_flight[READ]),
				       atomic_read(&shared->in_flight[WRITE]));
			}
		}
		dm_stat_free(&s->rcu_head);
	}
	free_percpu(stats->last);
}
