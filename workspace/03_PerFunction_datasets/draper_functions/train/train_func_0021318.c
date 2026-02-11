WRK_Init(void)
{
	pthread_t tp;

	AZ(pthread_cond_init(&herder_cond, NULL));
	Lck_New(&herder_mtx, lck_herder);
	Lck_New(&wstat_mtx, lck_wstat);

	wrk_addpools(params->wthread_pools);
	AZ(pthread_create(&tp, NULL, wrk_herdtimer_thread, NULL));
	AZ(pthread_detach(tp));
	AZ(pthread_create(&tp, NULL, wrk_herder_thread, NULL));
	AZ(pthread_detach(tp));
}
