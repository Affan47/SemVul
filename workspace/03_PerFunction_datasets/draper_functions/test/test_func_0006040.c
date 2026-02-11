wapi_thread_set_wait_handle (gpointer handle)
{
	struct _WapiHandle_thread *thread;
	gboolean ok;
	gpointer prev_handle;
	gpointer thread_handle;

	thread_handle = OpenThread (0, 0, GetCurrentThreadId ());
	ok = _wapi_lookup_handle (thread_handle, WAPI_HANDLE_THREAD,
							  (gpointer *)&thread);
	g_assert (ok);

	prev_handle = InterlockedCompareExchangePointer (&thread->wait_handle,
													 handle, NULL);
	_wapi_handle_unref (thread_handle);

	if (prev_handle == NULL) {

		_wapi_handle_ref (handle);

		WAIT_DEBUG (printf ("%p: state -> WAITING.\n", GetCurrentThreadId ()););
	} else {
		g_assert (prev_handle == INTERRUPTION_REQUESTED_HANDLE);
		WAIT_DEBUG (printf ("%p: unable to set state to WAITING.\n", GetCurrentThreadId ()););
	}

	return prev_handle == NULL;
}
