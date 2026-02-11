net_getsockport (int sok4, int sok6)
{
	struct sockaddr_in addr;
	int len = sizeof (addr);

	if (getsockname (sok4, (struct sockaddr *)&addr, &len) == -1)
		return -1;
	return addr.sin_port;
}
