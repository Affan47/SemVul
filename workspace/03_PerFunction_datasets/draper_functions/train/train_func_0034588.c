FindClose (gpointer handle)
{
	struct _WapiHandle_find *find_handle;
	gboolean ok;
	int thr_ret;

	if (handle == NULL) {
		SetLastError (ERROR_INVALID_HANDLE);
		return(FALSE);
	}

	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FIND,
				(gpointer *)&find_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up find handle %p", __func__,
			   handle);
		SetLastError (ERROR_INVALID_HANDLE);
		return(FALSE);
	}

	pthread_cleanup_push ((void(*)(void *))_wapi_handle_unlock_handle,
			      handle);
	thr_ret = _wapi_handle_lock_handle (handle);
	g_assert (thr_ret == 0);

	g_strfreev (find_handle->namelist);
	g_free (find_handle->dir_part);

	thr_ret = _wapi_handle_unlock_handle (handle);
	g_assert (thr_ret == 0);
	pthread_cleanup_pop (0);

	_wapi_handle_unref (handle);

	return(TRUE);
}
