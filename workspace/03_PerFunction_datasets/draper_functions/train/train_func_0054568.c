xmmsc_ipc_wait_for_event (xmmsc_ipc_t *ipc, unsigned int timeout)
{
	fd_set rfdset;
	fd_set wfdset;
	struct timeval tmout;
	xmms_socket_t fd;

	x_return_if_fail (ipc);
	x_return_if_fail (!ipc->disconnect);

	tmout.tv_sec = timeout;
	tmout.tv_usec = 0;

	fd = xmms_ipc_transport_fd_get (ipc->transport);

	FD_ZERO (&rfdset);
	FD_SET (fd, &rfdset);

	FD_ZERO (&wfdset);
	if (xmmsc_ipc_io_out (ipc)) {
		FD_SET (fd, &wfdset);
	}

	if (select (fd + 1, &rfdset, &wfdset, NULL, &tmout) == SOCKET_ERROR) {
		return;
	}

	if (FD_ISSET (fd, &rfdset)) {
		if (!xmmsc_ipc_io_in_callback (ipc)) {
			return;
		}
	}
	if (FD_ISSET (fd, &wfdset)) {
		xmmsc_ipc_io_out_callback (ipc);
	}
}
