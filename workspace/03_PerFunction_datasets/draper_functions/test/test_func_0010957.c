stratum_rthread(void *userdata)
{
	struct pool *pool = (struct pool *)userdata;
	char threadname[16];

	pthread_detach(pthread_self());

	snprintf(threadname, sizeof(threadname), "%d/RStratum", pool->pool_no);
	RenameThread(threadname);

	while (42) {
		struct timeval timeout;
		int sel_ret;
		fd_set rd;
		char *s;

		if (unlikely(pool->removed)) {
			suspend_stratum(pool);
			break;
		}


		if (!sock_full(pool) && !cnx_needed(pool)) {
			suspend_stratum(pool);
			clear_stratum_shares(pool);
			clear_pool_work(pool);

			wait_lpcurrent(pool);
			while (!restart_stratum(pool)) {
				if (pool->removed)
					goto out;
				if (enabled_pools > 1)
				cgsleep_ms(30000);
				else
					cgsleep_ms(3000);
			}
		}

		FD_ZERO(&rd);
		FD_SET(pool->sock, &rd);
		timeout.tv_sec = 90;
		timeout.tv_usec = 0;


		if (!sock_full(pool) && (sel_ret = select(pool->sock + 1, &rd, NULL, NULL, &timeout)) < 1) {
			applog(LOG_DEBUG, "Stratum select failed on pool %d with value %d", pool->pool_no, sel_ret);
			s = NULL;
		} else
			s = recv_line(pool);
		if (!s) {
			applog(LOG_NOTICE, "Stratum connection to pool %d interrupted", pool->pool_no);
			pool->getfail_occasions++;
			total_go++;


			if (!supports_resume(pool) || opt_lowmem)
				clear_stratum_shares(pool);
			clear_pool_work(pool);
			if (pool == current_pool())
				restart_threads();

			while (!restart_stratum(pool)) {
				if (pool->removed)
					goto out;
				cgsleep_ms(30000);
			}
			continue;
		}


		stratum_resumed(pool);

		if (!parse_method(pool, s) && !parse_stratum_response(pool, s))
			applog(LOG_INFO, "Unknown stratum msg: %s", s);
		else if (pool->swork.clean) {
			struct work *work = make_work();


			pool->swork.clean = false;
			gen_stratum_work(pool, work);
			work->longpoll = true;


			test_work_current(work);
			free_work(work);
		}
		free(s);
	}

out:
	return NULL;
}
