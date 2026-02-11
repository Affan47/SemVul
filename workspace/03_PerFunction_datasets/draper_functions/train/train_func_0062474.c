_wapi_accept(guint32 fd, struct sockaddr *addr, socklen_t *addrlen)
{
	gpointer handle = GUINT_TO_POINTER (fd);
	gpointer new_handle;
	struct _WapiHandle_socket *socket_handle;
	struct _WapiHandle_socket new_socket_handle = {0};
	gboolean ok;
	int new_fd;

	if (startup_count == 0) {
		WSASetLastError (WSANOTINITIALISED);
		return(INVALID_SOCKET);
	}

	if (addr != NULL && *addrlen < sizeof(struct sockaddr)) {
		WSASetLastError (WSAEFAULT);
		return(INVALID_SOCKET);
	}

	if (_wapi_handle_type (handle) != WAPI_HANDLE_SOCKET) {
		WSASetLastError (WSAENOTSOCK);
		return(INVALID_SOCKET);
	}

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_SOCKET,
				  (gpointer *)&socket_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up socket handle %p",
			   __func__, handle);
		WSASetLastError (WSAENOTSOCK);
		return(INVALID_SOCKET);
	}

	do {
		new_fd = accept (fd, addr, addrlen);
	} while (new_fd == -1 && errno == EINTR &&
		 !_wapi_thread_cur_apc_pending());

	if (new_fd == -1) {
		gint errnum = errno;
		DEBUG ("%s: accept error: %s", __func__, strerror(errno));

		errnum = errno_to_WSA (errnum, __func__);
		WSASetLastError (errnum);

		return(INVALID_SOCKET);
	}

	if (new_fd >= _wapi_fd_reserve) {
		DEBUG ("%s: File descriptor is too big", __func__);

		WSASetLastError (WSASYSCALLFAILURE);

		close (new_fd);

		return(INVALID_SOCKET);
	}

	new_socket_handle.domain = socket_handle->domain;
	new_socket_handle.type = socket_handle->type;
	new_socket_handle.protocol = socket_handle->protocol;
	new_socket_handle.still_readable = 1;

	new_handle = _wapi_handle_new_fd (WAPI_HANDLE_SOCKET, new_fd,
					  &new_socket_handle);
	if(new_handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating socket handle", __func__);
		WSASetLastError (ERROR_GEN_FAILURE);
		return(INVALID_SOCKET);
	}

	DEBUG ("%s: returning newly accepted socket handle %p with",
		   __func__, new_handle);

	return(new_fd);
}
