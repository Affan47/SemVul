CreatePipe (gpointer *readpipe, gpointer *writepipe,
		     WapiSecurityAttributes *security G_GNUC_UNUSED, guint32 size)
{
	struct _WapiHandle_file pipe_read_handle = {0};
	struct _WapiHandle_file pipe_write_handle = {0};
	gpointer read_handle;
	gpointer write_handle;
	int filedes[2];
	int ret;

	mono_once (&io_ops_once, io_ops_init);

	DEBUG ("%s: Creating pipe", __func__);

	ret=pipe (filedes);
	if(ret==-1) {
		DEBUG ("%s: Error creating pipe: %s", __func__,
			   strerror (errno));

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}

	if (filedes[0] >= _wapi_fd_reserve ||
	    filedes[1] >= _wapi_fd_reserve) {
		DEBUG ("%s: File descriptor is too big", __func__);

		SetLastError (ERROR_TOO_MANY_OPEN_FILES);

		close (filedes[0]);
		close (filedes[1]);

		return(FALSE);
	}


	pipe_read_handle.fd = filedes [0];
	pipe_read_handle.fileaccess = GENERIC_READ;
	read_handle = _wapi_handle_new_fd (WAPI_HANDLE_PIPE, filedes[0],
					   &pipe_read_handle);
	if (read_handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating pipe read handle", __func__);
		close (filedes[0]);
		close (filedes[1]);
		SetLastError (ERROR_GEN_FAILURE);

		return(FALSE);
	}

	pipe_write_handle.fd = filedes [1];
	pipe_write_handle.fileaccess = GENERIC_WRITE;
	write_handle = _wapi_handle_new_fd (WAPI_HANDLE_PIPE, filedes[1],
					    &pipe_write_handle);
	if (write_handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating pipe write handle", __func__);
		_wapi_handle_unref (read_handle);

		close (filedes[0]);
		close (filedes[1]);
		SetLastError (ERROR_GEN_FAILURE);

		return(FALSE);
	}

	*readpipe = read_handle;
	*writepipe = write_handle;

	DEBUG ("%s: Returning pipe: read handle %p, write handle %p",
		   __func__, read_handle, write_handle);

	return(TRUE);
}
