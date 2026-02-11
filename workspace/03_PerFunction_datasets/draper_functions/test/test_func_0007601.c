transport_handshake (void)
{
	char handshake_msg [128];
	guint8 buf [128];
	int res;

	disconnected = TRUE;


	sprintf (handshake_msg, "DWP-Handshake");

	MONO_PREPARE_BLOCKING;
	do {
		res = transport_send (handshake_msg, strlen (handshake_msg));
	} while (res == -1 && get_last_sock_error () == MONO_EINTR);
	MONO_FINISH_BLOCKING;

	g_assert (res != -1);


	MONO_PREPARE_BLOCKING;
	res = transport_recv (buf, strlen (handshake_msg));
	MONO_FINISH_BLOCKING;
	if ((res != strlen (handshake_msg)) || (memcmp (buf, handshake_msg, strlen (handshake_msg)) != 0)) {
		fprintf (stderr, "debugger-agent: DWP handshake failed.\n");
		return FALSE;
	}


	major_version = MAJOR_VERSION;
	minor_version = MINOR_VERSION;
	protocol_version_set = FALSE;

#ifndef DISABLE_SOCKET_TRANSPORT


	if (conn_fd) {
		int flag = 1;
		int result = setsockopt (conn_fd,
                                 IPPROTO_TCP,
                                 TCP_NODELAY,
                                 (char *) &flag,
                                 sizeof(int));
		g_assert (result >= 0);
	}

	set_keepalive ();
#endif

	disconnected = FALSE;
	return TRUE;
}
