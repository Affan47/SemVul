clear_stratum_shares(struct pool *pool)
{
	struct stratum_share *sshare, *tmpshare;
	double diff_cleared = 0;
	int cleared = 0;

	mutex_lock(&sshare_lock);
	HASH_ITER(hh, stratum_shares, sshare, tmpshare) {
		if (sshare->work->pool == pool) {
			HASH_DEL(stratum_shares, sshare);
			diff_cleared += sshare->work->work_difficulty;
			free_work(sshare->work);
			pool->sshares--;
			free(sshare);
			cleared++;
		}
	}
	mutex_unlock(&sshare_lock);

	if (cleared) {
		applog(LOG_WARNING, "Lost %d shares due to stratum disconnect on pool %d", cleared, pool->pool_no);
		pool->stale_shares += cleared;
		total_stale += cleared;
		pool->diff_stale += diff_cleared;
		total_diff_stale += diff_cleared;
	}
}
