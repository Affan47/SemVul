namedmutex_release (gpointer handle)
{
	struct _WapiHandle_namedmutex *mutex_handle;
	gboolean ok;
	pthread_t tid = pthread_self ();
	pid_t pid = _wapi_getpid ();
	int thr_ret;
	gboolean ret = FALSE;

	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_NAMEDMUTEX,
				(gpointer *)&mutex_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up named mutex handle %p",
			   __func__, handle);
		return(FALSE);
	}

	thr_ret = _wapi_handle_lock_shared_handles ();
	g_assert (thr_ret == 0);

	DEBUG("%s: Releasing mutex handle %p", __func__, handle);

	if (!pthread_equal (mutex_handle->tid, tid) ||
	    mutex_handle->pid != pid) {
		DEBUG("%s: We don't own mutex handle %p (owned by %d:%ld, me %d:%ld)", __func__, handle, mutex_handle->pid, mutex_handle->tid, _wapi_getpid (), tid);

		goto cleanup;
	}
	ret = TRUE;


	mutex_handle->recursion--;

	if(mutex_handle->recursion==0) {
		_wapi_thread_disown_mutex (handle);

		DEBUG("%s: Unlocking mutex handle %p", __func__, handle);

		mutex_handle->pid=0;
		mutex_handle->tid=0;
		_wapi_shared_handle_set_signal_state (handle, TRUE);
	}

cleanup:
	_wapi_handle_unlock_shared_handles ();

	return(ret);
}
