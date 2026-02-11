stop_mac_discovery(void)
{
	if (!thr_running) {
		printf("mac discoverer isn't running\n");
		return -1;
	}
	stop = 1;
	pthread_mutex_lock(&mutex_stop);
	pthread_cond_signal(&cond_stop);
	pthread_mutex_unlock(&mutex_stop);
	pthread_join(mac_thr, NULL);
	thr_running = 0;
	return 0;
}
