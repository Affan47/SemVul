suspend_current (void)
{
	int err;
	DebuggerTlsData *tls;

	g_assert (debugger_thread_id != GetCurrentThreadId ());

	if (mono_loader_lock_is_owned_by_self ()) {


		return;
	}

 	tls = mono_native_tls_get_value (debugger_tls_id);
	g_assert (tls);

	mono_mutex_lock (&suspend_mutex);

	tls->suspending = FALSE;
	tls->really_suspended = TRUE;

	if (!tls->suspended) {
		tls->suspended = TRUE;
		MONO_SEM_POST (&suspend_sem);
	}

	DEBUG(1, fprintf (log_file, "[%p] Suspended.\n", (gpointer)GetCurrentThreadId ()));

	while (suspend_count - tls->resume_count > 0) {
#ifdef HOST_WIN32
		if (WAIT_TIMEOUT == WaitForSingleObject(suspend_cond, 0))
		{
			mono_mutex_unlock (&suspend_mutex);
			Sleep(1);
			mono_mutex_lock (&suspend_mutex);
		}
		else
		{
		}
#else
		err = mono_cond_wait (&suspend_cond, &suspend_mutex);
		g_assert (err == 0);
#endif
	}

	tls->suspended = FALSE;
	tls->really_suspended = FALSE;

	threads_suspend_count --;

	mono_mutex_unlock (&suspend_mutex);

	DEBUG(1, fprintf (log_file, "[%p] Resumed.\n", (gpointer)GetCurrentThreadId ()));

	if (tls->pending_invoke) {

		tls->pending_invoke->has_ctx = TRUE;
		tls->pending_invoke->ctx = tls->context.ctx;

		invoke_method ();
	}


	tls->context.valid = FALSE;
	tls->async_state.valid = FALSE;
	invalidate_frames (tls);
}
