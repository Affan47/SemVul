srv_wake_purge_thread_if_not_active(void)

{
	ut_ad(!mutex_own(&kernel_mutex));

	if (srv_n_purge_threads > 0
	    && srv_n_threads_active[SRV_WORKER] == 0) {

		mutex_enter(&kernel_mutex);

		srv_release_threads(SRV_WORKER, 1);

		mutex_exit(&kernel_mutex);
	}
}
