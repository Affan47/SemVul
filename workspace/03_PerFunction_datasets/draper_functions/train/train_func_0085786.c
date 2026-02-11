resume_thread (MonoInternalThread *thread)
{
	int err;
	DebuggerTlsData *tls;

	g_assert (debugger_thread_id == GetCurrentThreadId ());

	mono_loader_lock ();

	tls = mono_g_hash_table_lookup (thread_to_tls, thread);
	g_assert (tls);

	mono_mutex_lock (&suspend_mutex);

	g_assert (suspend_count > 0);

	DEBUG(1, fprintf (log_file, "[%p] Resuming thread...\n", (gpointer)(gssize)thread->tid));

	tls->resume_count += suspend_count;


	err = mono_cond_broadcast (&suspend_cond);
	g_assert (err == 0);

	mono_mutex_unlock (&suspend_mutex);


	mono_loader_unlock ();
}
