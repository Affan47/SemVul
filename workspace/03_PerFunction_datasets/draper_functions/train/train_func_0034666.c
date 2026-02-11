appdomain_unload (MonoProfiler *prof, MonoDomain *domain)
{
	DebuggerTlsData *tls;

	if (is_debugger_thread ())
		return;

	tls = (DebuggerTlsData *)mono_native_tls_get_value (debugger_tls_id);
	g_assert (tls);
	tls->domain_unloading = NULL;

	clear_breakpoints_for_domain (domain);

	mono_loader_lock ();

	mono_g_hash_table_foreach (thread_to_tls, invalidate_each_thread, NULL);
	mono_loader_unlock ();

	process_profiler_event (EVENT_KIND_APPDOMAIN_UNLOAD, domain);
}
