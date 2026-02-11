_wp_open_listenfd (int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in servaddr;

	if ((listenfd = wp_socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -1;
	}

	if (wp_setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof (int)) < 0)
	{
		return -2;
	}

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons ((unsigned short)port);

	if (wp_bind (listenfd, (struct sockaddr*)&servaddr, sizeof (servaddr)) < 0)
	{
		return -3;
	}

	if (wp_listen (listenfd, LISTENQ) < 0)
	{
		return -4;
	}

	return listenfd;
}
