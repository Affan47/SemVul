dm_stats_clear(struct dm_stats *stats, int id)
{
	struct dm_stat *s;

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unlock(&stats->mutex);
		return -ENOENT;
	}

	__dm_stat_clear(s, 0, s->n_entries, true);

	mutex_unlock(&stats->mutex);

	return 1;
}
