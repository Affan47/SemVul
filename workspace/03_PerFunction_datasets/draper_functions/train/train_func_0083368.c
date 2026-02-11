_wapi_stdhandle_create (int fd, const gchar *name)
{
	struct _WapiHandle_file file_handle = {0};
	gpointer handle;
	int flags;

	DEBUG("%s: creating standard handle type %s, fd %d", __func__,
		  name, fd);

#if !defined(__native_client__)

	do {
		flags=fcntl(fd, F_GETFL);
	} while (flags == -1 && errno == EINTR);

	if(flags==-1) {


		DEBUG("%s: fcntl error on fd %d: %s", __func__, fd,
			  strerror(errno));

		SetLastError (_wapi_get_win32_file_error (errno));
		return(INVALID_HANDLE_VALUE);
	}
	file_handle.fileaccess=convert_from_flags(flags);
#else


	file_handle.fileaccess = (fd == STDIN_FILENO) ? GENERIC_READ : GENERIC_WRITE;
#endif

	file_handle.fd = fd;
	file_handle.filename = g_strdup(name);

	file_handle.security_attributes=0;


	if (fd == 0) {
		file_handle.fileaccess &= ~GENERIC_WRITE;
	}

	file_handle.sharemode=0;
	file_handle.attrs=0;

	handle = _wapi_handle_new_fd (WAPI_HANDLE_CONSOLE, fd, &file_handle);
	if (handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating file handle", __func__);
		SetLastError (ERROR_GEN_FAILURE);
		return(INVALID_HANDLE_VALUE);
	}

	DEBUG("%s: returning handle %p", __func__, handle);

	return(handle);
}
