wapi_thread_interrupt_self (void)
{
	HANDLE handle;
	struct _WapiHandle_thread *thread_handle;
	gboolean ok;

	handle = _wapi_thread_handle_from_id (pthread_self ());
	g_assert (handle);

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_THREAD,
				  (gpointer *)&thread_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up thread handle %p", __func__,
			   handle);
		return;
	}


	thread_handle->has_apc = TRUE;
}
