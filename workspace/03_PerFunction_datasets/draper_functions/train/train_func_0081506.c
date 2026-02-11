unload_module(void)
{
	int res;

	ast_mutex_lock(&timing_thread.lock);
	timing_thread.stop = 1;
	ast_cond_signal(&timing_thread.cond);
	ast_mutex_unlock(&timing_thread.lock);
	pthread_join(timing_thread.thread, NULL);

	if (!(res = ast_unregister_timing_interface(timing_funcs_handle))) {
		ao2_ref(pthread_timers, -1);
		pthread_timers = NULL;
	}

	return res;
}
