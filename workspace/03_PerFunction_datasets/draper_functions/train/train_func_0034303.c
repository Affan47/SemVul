negotiate(int s, char *lu, char *assoc)
{

	if (setsockopt(s, SOL_SOCKET, SO_OOBINLINE, (char *)&on,
		    sizeof(on)) < 0) {
		popup_a_sockerr("setsockopt(SO_OOBINLINE)");
		return -1;
	}
	if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char *)&on,
		    sizeof(on)) < 0) {
		popup_a_sockerr("setsockopt(SO_KEEPALIVE)");
		return -1;
	}

#if !defined(_WIN32)

	(void) fcntl(s, F_SETFD, 1);
#endif


#if defined(HAVE_LIBSSL)
	if (ssl_host && !secure_connection) {
		ssl_init();
		if (ssl_con == NULL)
			return -1;
		SSL_set_fd(ssl_con, s);
		if (!SSL_connect(ssl_con)) {
			popup_a_sockerr("SSL_connect failed");
			return -1;
		}
		secure_connection = True;
		vtrace_str("TLS/DDL tunneled connection complete.  "
			   "Connection is now secure.\n");
	}
#endif


	if (netrbuf == NULL)
		netrbuf = (unsigned char *)Malloc(BUFSZ);
	if (ibuf == NULL)
		ibuf = (unsigned char *)Malloc(BUFSIZ);
	ibuf_size = BUFSIZ;
	ibptr = ibuf;


	setup_lus(lu, assoc);


	(void) memset((char *) myopts, 0, sizeof(myopts));
	(void) memset((char *) hisopts, 0, sizeof(hisopts));
	e_funcs = E_OPT(TN3270E_FUNC_BIND_IMAGE) |
		  E_OPT(TN3270E_FUNC_DATA_STREAM_CTL) |
		  E_OPT(TN3270E_FUNC_RESPONSES) |
		  E_OPT(TN3270E_FUNC_SCS_CTL_CODES) |
		  E_OPT(TN3270E_FUNC_SYSREQ);
	e_xmit_seq = 0;
	response_required = TN3270E_RSF_NO_RESPONSE;
#if defined(HAVE_LIBSSL)
	need_tls_follows = False;
#endif
	telnet_state = TNS_DATA;


	(void) time(&ns_time);
	ns_brcvd = 0;
	ns_rrcvd = 0;
	ns_bsent = 0;
	ns_rsent = 0;
	syncing = 0;
	tn3270e_negotiated = 0;
	tn3270e_submode = E_NONE;
	tn3270e_bound = 0;


	cstate = CONNECTED_INITIAL;
	sock = s;
	while (!tn3270e_negotiated &&
	       cstate != CONNECTED_3270 &&
	       cstate != NOT_CONNECTED) {

		if (net_input(s) < 0)
			return -1;
	}


	return 0;
}
