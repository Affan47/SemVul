submit_work_async(struct work *work)
{
	struct pool *pool = work->pool;
	pthread_t submit_thread;

	cgtime(&work->tv_work_found);

	if (stale_work(work, true)) {
		if (opt_submit_stale)
			applog(LOG_NOTICE, "Pool %d stale share detected, submitting as user requested", pool->pool_no);
		else if (pool->submit_old)
			applog(LOG_NOTICE, "Pool %d stale share detected, submitting as pool requested", pool->pool_no);
		else {
			applog(LOG_NOTICE, "Pool %d stale share detected, discarding", pool->pool_no);
			sharelog("discard", work);

			mutex_lock(&stats_lock);
			total_stale++;
			pool->stale_shares++;
			total_diff_stale += work->work_difficulty;
			pool->diff_stale += work->work_difficulty;
			mutex_unlock(&stats_lock);

			free_work(work);
			return;
		}
		work->stale = true;
	}

	if (work->stratum) {
		applog(LOG_DEBUG, "Pushing pool %d work to stratum queue", pool->pool_no);
		if (unlikely(!tq_push(pool->stratum_q, work))) {
			applog(LOG_DEBUG, "Discarding work from removed pool");
			free_work(work);
		}
	} else {
		applog(LOG_DEBUG, "Pushing submit work to work thread");
		if (unlikely(pthread_create(&submit_thread, NULL, submit_work_thread, (void *)work)))
			quit(1, "Failed to create submit_work_thread");
	}
}
