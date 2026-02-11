worker_try_unpark (void)
{
	gboolean res = FALSE;

	mono_trace (G_LOG_LEVEL_DEBUG, MONO_TRACE_THREADPOOL, "[%p] try unpark worker", mono_native_thread_id_get ());

	mono_coop_mutex_lock (&threadpool->active_threads_lock);
	if (threadpool->parked_threads_count > 0) {
		mono_coop_cond_signal (&threadpool->parked_threads_cond);
		res = TRUE;
	}
	mono_coop_mutex_unlock (&threadpool->active_threads_lock);

	mono_trace (G_LOG_LEVEL_DEBUG, MONO_TRACE_THREADPOOL, "[%p] try unpark worker, success? %s", mono_native_thread_id_get (), res ? "yes" : "no");

	return res;
}
