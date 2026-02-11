net_getsockname(GIOChannel *handle, IPADDR *addr, int *port)
{
	union sockaddr_union so;
	socklen_t addrlen;

	g_return_val_if_fail(handle != NULL, -1);
	g_return_val_if_fail(addr != NULL, -1);

	addrlen = sizeof(so);
	if (getsockname(g_io_channel_unix_get_fd(handle),
			(struct sockaddr *) &so, &addrlen) == -1)
		return -1;

        sin_get_ip(&so, addr);
	if (port) *port = sin_get_port(&so);

	return 0;
}
