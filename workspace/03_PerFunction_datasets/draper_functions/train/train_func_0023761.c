wait_for_attach (void)
{
#ifndef DISABLE_SOCKET_TRANSPORT
	if (listen_fd == -1) {
		DEBUG (1, fprintf (log_file, "[dbg] Invalid listening socket\n"));
		return FALSE;
	}


	conn_fd = socket_transport_accept (listen_fd);
	DEBUG (1, fprintf (log_file, "Accepted connection on %d\n", conn_fd));
	if (conn_fd == -1) {
		DEBUG (1, fprintf (log_file, "[dbg] Bad client connection\n"));
		return FALSE;
	}
#else
	g_assert_not_reached ();
#endif


	disconnected = !transport_handshake ();
	if (disconnected) {
		DEBUG (1, fprintf (log_file, "Transport handshake failed!\n"));
		return FALSE;
	}

	return TRUE;
}
