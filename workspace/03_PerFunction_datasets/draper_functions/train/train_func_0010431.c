file_read(gpointer handle, gpointer buffer,
			  guint32 numbytes, guint32 *bytesread,
			  WapiOverlapped *overlapped)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	int fd, ret;

	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (ERROR_INVALID_HANDLE);
		return(FALSE);
	}

	fd = file_handle->fd;
	if(bytesread!=NULL) {
		*bytesread=0;
	}

	if(!(file_handle->fileaccess & GENERIC_READ) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
		DEBUG("%s: handle %p doesn't have GENERIC_READ access: %u",
			  __func__, handle, file_handle->fileaccess);

		SetLastError (ERROR_ACCESS_DENIED);
		return(FALSE);
	}

	do {
		ret = read (fd, buffer, numbytes);
	} while (ret == -1 && errno == EINTR &&
		 !_wapi_thread_cur_apc_pending());

	if(ret==-1) {
		gint err = errno;

		DEBUG("%s: read of handle %p error: %s", __func__,
			  handle, strerror(err));
		SetLastError (_wapi_get_win32_file_error (err));
		return(FALSE);
	}

	if (bytesread != NULL) {
		*bytesread = ret;
	}

	return(TRUE);
}
