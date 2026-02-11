hdhomerun_debug_create(void)
{
	struct hdhomerun_debug_t *dbg = (struct hdhomerun_debug_t *)calloc(1, sizeof(struct hdhomerun_debug_t));
	if (!dbg) {
		return NULL;
	}

	dbg->sock = HDHOMERUN_SOCK_INVALID;

	pthread_mutex_init(&dbg->print_lock, NULL);
	pthread_mutex_init(&dbg->queue_lock, NULL);
	pthread_mutex_init(&dbg->send_lock, NULL);

	if (pthread_create(&dbg->thread, NULL, &hdhomerun_debug_thread_execute, dbg) != 0) {
		free(dbg);
		return NULL;
	}

	return dbg;
}
