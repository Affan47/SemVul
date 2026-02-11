auth_mgr_swap_in()
{
	if (auth_mgr.overflow[auth_mgr.of_tail] != NULL) {
		LogDebug("waking up thread %lddd, auth slot has opened", THREAD_ID);

		COND_SIGNAL(auth_mgr.overflow[auth_mgr.of_tail]);
		auth_mgr.overflow[auth_mgr.of_tail] = NULL;
		auth_mgr.of_tail = (auth_mgr.of_tail + 1) % auth_mgr.overflow_size;
	} else {

		LogDebug("no threads need to be signaled.");
	}
}
