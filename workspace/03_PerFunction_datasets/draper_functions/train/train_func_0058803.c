try_tcp (struct x_socket *s, int dpy)
{
    struct sockaddr_in tcpaddr;
    struct in_addr local;
    int one = 1;
    int fd;

    memset(&local, 0, sizeof(local));
    local.s_addr = htonl(INADDR_LOOPBACK);

    fd = socket (AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
	err (1, "socket AF_INET");
#if defined(TCP_NODELAY) && defined(HAVE_SETSOCKOPT)
    setsockopt (fd, IPPROTO_TCP, TCP_NODELAY, (void *)&one,
		sizeof(one));
#endif
    memset (&tcpaddr, 0, sizeof(tcpaddr));
    tcpaddr.sin_family = AF_INET;
    tcpaddr.sin_addr = local;
    tcpaddr.sin_port = htons(6000 + dpy);
    if (bind (fd, (struct sockaddr *)&tcpaddr,
	      sizeof(tcpaddr)) < 0) {
	close (fd);
	if (errno == EADDRINUSE)
	    return 1;
	else
	    return -1;
    }
    s->fd = fd;
    s->pathname = NULL;
    s->flags = TCP;
    return 0;
}
