net_geterror(GIOChannel *handle)
{
	int data;
	socklen_t len = sizeof(data);

	if (getsockopt(g_io_channel_unix_get_fd(handle),
		       SOL_SOCKET, SO_ERROR, (void *) &data, &len) == -1)
		return -1;

	return data;
}
