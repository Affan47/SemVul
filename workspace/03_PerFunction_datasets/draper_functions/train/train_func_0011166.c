connect_to_internet_server (const char *serverhost, u_short port)
{
	int s;
	struct servent *sp;
	struct sockaddr_in peeraddr_in;
	char buf[512];


	memset (&peeraddr_in, 0, sizeof (struct sockaddr_in));


	peeraddr_in.sin_family = AF_INET;


	peeraddr_in.sin_addr.s_addr = glibtop_internet_addr (serverhost);
	if ((long) peeraddr_in.sin_addr.s_addr == -1)
		glibtop_error ("unable to find %s in /etc/hosts or from YP", serverhost);

	if (port == 0) {
		if ((sp = getservbyname ("gtopd", "tcp")) == NULL)
			peeraddr_in.sin_port = htons (DEFAULT_PORT + getuid ());
		else
			peeraddr_in.sin_port = sp->s_port;
	}

	else
		peeraddr_in.sin_port = htons (port);


	if ((s = socket (AF_INET, SOCK_STREAM, 0)) == -1)
		glibtop_error_io ("unable to create socket");


	if (connect (s, (struct sockaddr *) &peeraddr_in,
		     sizeof (struct sockaddr_in)) == -1)
		  glibtop_error_io ("unable to connect to remote");

#ifdef AUTH_MAGIC_COOKIE


	sprintf (buf, "%d", port);

	server_xauth =
		XauGetAuthByAddr (FamilyInternet,
				  sizeof (peeraddr_in.sin_addr.s_addr),
				  (char *) &peeraddr_in.sin_addr.s_addr,
				  strlen (buf), buf,
				  strlen (MCOOKIE_X_NAME), MCOOKIE_X_NAME);

	if (server_xauth && server_xauth->data) {
		sprintf (buf, "%s\n%d\n", MCOOKIE_NAME, server_xauth->data_length);
		write (s, buf, strlen (buf));
		write (s, server_xauth->data, server_xauth->data_length);

		return (s);
	}
#endif

	sprintf (buf, "%s\n", DEFAUTH_NAME);
	write (s, buf, strlen (buf));

	return (s);

}
