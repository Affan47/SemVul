tcp_set_blocking_mode(rdpTcp* tcp, boolean blocking)
{
	int flags;
	flags = fcntl(tcp->sockfd, F_GETFL);

	if (flags == -1)
	{
		printf("transport_configure_sockfd: fcntl failed.\n");
		return False;
	}

	if (blocking == True)
	{

		fcntl(tcp->sockfd, F_SETFL, flags & ~(O_NONBLOCK));
	}
	else
	{

		fcntl(tcp->sockfd, F_SETFL, flags | O_NONBLOCK);
	}

	return True;
}
