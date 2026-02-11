file_flush(gpointer handle)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	int ret, fd;

	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (ERROR_INVALID_HANDLE);
		return(FALSE);
	}

	fd = file_handle->fd;

	if(!(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
		DEBUG("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);

		SetLastError (ERROR_ACCESS_DENIED);
		return(FALSE);
	}

	ret=fsync(fd);
	if (ret==-1) {
		DEBUG("%s: fsync of handle %p error: %s", __func__, handle,
			  strerror(errno));

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}

	return(TRUE);
}
