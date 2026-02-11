cfqg_stats_set_start_empty_time(struct cfq_group *cfqg)
{
	struct cfqg_stats *stats = &cfqg->stats;

	if (blkg_rwstat_total(&stats->queued))
		return;


	if (cfqg_stats_empty(stats))
		return;

	stats->start_empty_time = sched_clock();
	cfqg_stats_mark_empty(stats);
}
