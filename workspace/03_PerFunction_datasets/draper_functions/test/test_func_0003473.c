prune_stratum_shares(struct pool *pool)
{
	struct stratum_share *sshare, *tmpshare;
	time_t current_time = time(NULL);
	int cleared = 0;

	mutex_lock(&sshare_lock);
	HASH_ITER(hh, stratum_shares, sshare, tmpshare) {
		if (sshare->work->pool == pool && current_time > sshare->sshare_time + 120) {
			HASH_DEL(stratum_shares, sshare);
			free_work(sshare->work);
			free(sshare);
			cleared++;
		}
	}
	mutex_unlock(&sshare_lock);

	if (cleared) {
		applog(LOG_WARNING, "Lost %d shares due to no stratum share response from pool %d",
		       cleared, pool->pool_no);
		pool->stale_shares += cleared;
		total_stale += cleared;
	}
}
