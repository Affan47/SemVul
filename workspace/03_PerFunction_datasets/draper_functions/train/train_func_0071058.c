namedsem_release (gpointer handle, gint32 count,
				  gint32 *prevcount)
{
	struct _WapiHandle_namedsem *sem_handle;
	gboolean ok;
	gboolean ret=FALSE;
	int thr_ret;

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_NAMEDSEM,
				  (gpointer *)&sem_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up sem handle %p", __func__,
			   handle);
		return(FALSE);
	}

	thr_ret = _wapi_handle_lock_shared_handles ();
	g_assert (thr_ret == 0);

	DEBUG("%s: named sem %p val %d count %d", __func__, handle,
		  sem_handle->val, count);


	if (prevcount != NULL) {
		*prevcount = sem_handle->val;
	}


	if (sem_handle->val + count > (guint32)sem_handle->max) {
		DEBUG ("%s: named sem %p max value would be exceeded: max %d current %d count %d", __func__, handle, sem_handle->max, sem_handle->val, count);

		goto end;
	}

	sem_handle->val += count;
	_wapi_shared_handle_set_signal_state (handle, TRUE);

	ret = TRUE;

	DEBUG("%s: named sem %p val now %d", __func__, handle,
		  sem_handle->val);

end:
	_wapi_handle_unlock_shared_handles ();

	return(ret);
}
