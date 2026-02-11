nodename(int mayoverride)
{
	static char *hostname;
	char *hn;
        struct utsname ut;
#ifdef	HAVE_SOCKETS
#ifdef	HAVE_IPv6_FUNCS
	struct addrinfo hints, *res;
#else
        struct hostent *hent;
#endif
#endif

	if (mayoverride && (hn = value("hostname")) != NULL && *hn) {
		free(hostname);
		hostname = sstrdup(hn);
	}
	if (hostname == NULL) {
		uname(&ut);
		hn = ut.nodename;
#ifdef	HAVE_SOCKETS
#ifdef	HAVE_IPv6_FUNCS
		memset(&hints, 0, sizeof hints);
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_CANONNAME;
		if (getaddrinfo(hn, "0", &hints, &res) == 0) {
			if (res->ai_canonname) {
				hn = salloc(strlen(res->ai_canonname) + 1);
				strcpy(hn, res->ai_canonname);
			}
			freeaddrinfo(res);
		}
#else
		hent = gethostbyname(hn);
		if (hent != NULL) {
			hn = hent->h_name;
		}
#endif
#endif
		hostname = smalloc(strlen(hn) + 1);
		strcpy(hostname, hn);
	}
	return hostname;
}
