wapi_disconnectex (guint32 fd, WapiOverlapped *overlapped,
				   guint32 flags, guint32 reserved)
{
	DEBUG ("%s: called on socket %d!", __func__, fd);

	if (reserved != 0) {
		WSASetLastError (WSAEINVAL);
		return(FALSE);
	}


	return(socket_disconnect (fd));
}
