event_set (gpointer handle)
{
	struct _WapiHandle_event *event_handle;
	gboolean ok;
	int thr_ret;

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_EVENT,
				  (gpointer *)&event_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up event handle %p", __func__,
			   handle);
		return(FALSE);
	}

	pthread_cleanup_push ((void(*)(void *))_wapi_handle_unlock_handle,
			      handle);
	thr_ret = _wapi_handle_lock_handle (handle);
	g_assert (thr_ret == 0);

	DEBUG ("%s: Setting event handle %p", __func__, handle);

	if (event_handle->manual == TRUE) {
		_wapi_handle_set_signal_state (handle, TRUE, TRUE);
	} else {
		event_handle->set_count = 1;
		_wapi_handle_set_signal_state (handle, TRUE, FALSE);
	}

	thr_ret = _wapi_handle_unlock_handle (handle);
	g_assert (thr_ret == 0);

	pthread_cleanup_pop (0);

	return(TRUE);
}
