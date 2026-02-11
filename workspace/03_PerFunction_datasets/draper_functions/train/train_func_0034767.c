t_pool_next_result_wait(t_results_queue *q) {
    t_pool_result *r;

#ifdef DEBUG
    fprintf(stderr, "Waiting for result %d...\n", q->next_serial);
#endif

    pthread_mutex_lock(&q->result_m);
    while (!(r = t_pool_next_result_locked(q))) {

	struct timeval now;
	struct timespec timeout;

	gettimeofday(&now, NULL);
	timeout.tv_sec = now.tv_sec + 10;
	timeout.tv_nsec = now.tv_usec * 1000;

	pthread_cond_timedwait(&q->result_avail_c, &q->result_m, &timeout);
    }
    pthread_mutex_unlock(&q->result_m);

    return r;
}
