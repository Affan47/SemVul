make_listen_socket (krb5_context context, const char *port_str)
{
    krb5_socket_t fd;
    int one = 1;
    struct sockaddr_in addr;

    fd = socket (AF_INET, SOCK_STREAM, 0);
    if (rk_IS_BAD_SOCKET(fd))
	krb5_err (context, 1, rk_SOCK_ERRNO, "socket AF_INET");
    setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, (void *)&one, sizeof(one));
    memset (&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;

    if (port_str) {
	addr.sin_port = krb5_getportbyname (context,
					      port_str, "tcp",
					      0);
	if (addr.sin_port == 0) {
	    char *ptr;
	    long port;

	    port = strtol (port_str, &ptr, 10);
	    if (port == 0 && ptr == port_str)
		krb5_errx (context, 1, "bad port `%s'", port_str);
	    addr.sin_port = htons(port);
	}
    } else {
	addr.sin_port = krb5_getportbyname (context, IPROP_SERVICE,
					    "tcp", IPROP_PORT);
    }
    if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	krb5_err (context, 1, errno, "bind");
    if (listen(fd, SOMAXCONN) < 0)
	krb5_err (context, 1, errno, "listen");
    return fd;
}
