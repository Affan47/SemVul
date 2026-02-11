worker_request (MonoDomain *domain)
{
	ThreadPoolDomain *tpdomain;

	g_assert (domain);
	g_assert (threadpool);

	if (mono_runtime_is_shutting_down ())
		return FALSE;

	mono_coop_mutex_lock (&threadpool->domains_lock);


	if (mono_domain_is_unloading (domain)) {
		mono_coop_mutex_unlock (&threadpool->domains_lock);
		return FALSE;
	}

	tpdomain = domain_get (domain, TRUE);
	g_assert (tpdomain);
	tpdomain->outstanding_request ++;

	mono_trace (G_LOG_LEVEL_DEBUG, MONO_TRACE_THREADPOOL, "[%p] request worker, domain = %p, outstanding_request = %d",
		mono_native_thread_id_get (), tpdomain->domain, tpdomain->outstanding_request);

	mono_coop_mutex_unlock (&threadpool->domains_lock);

	if (threadpool->suspended)
		return FALSE;

	monitor_ensure_running ();

	if (worker_try_unpark ()) {
		mono_trace (G_LOG_LEVEL_DEBUG, MONO_TRACE_THREADPOOL, "[%p] request worker, unparked", mono_native_thread_id_get ());
		return TRUE;
	}

	if (worker_try_create ()) {
		mono_trace (G_LOG_LEVEL_DEBUG, MONO_TRACE_THREADPOOL, "[%p] request worker, created", mono_native_thread_id_get ());
		return TRUE;
	}

	mono_trace (G_LOG_LEVEL_DEBUG, MONO_TRACE_THREADPOOL, "[%p] request worker, failed", mono_native_thread_id_get ());
	return FALSE;
}
