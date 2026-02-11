is_url_ipv6(const char *url) {
	struct addrinfo *aitop;
	int gaierrno;
	struct addrinfo hints;
	char hostname[CA_MAXHOSTNAMELEN+1];
	const char *p, *p2, *p3;
	int ret;

	p = strstr (url, "://");
	if (!p)
		return (0);

	p += 3;
	while (*p == '/') ++p;

	if (!*p)
		return (0);

	p2 = strchr (p, '/');
	p3 = strchr (p, ']');

	if (p2 && p3 && p3>p2)
		p3 = NULL;

	if (*p == '[' && p3) {
		if (p3 - p >= CA_MAXHOSTNAMELEN)
			return (0);
		strncpy (hostname, p, p3 - p + 1);
		hostname[p3-p+1] = '\0';
	} else if (p2) {
		if (p2 - p > CA_MAXHOSTNAMELEN)
			return (0);
		strncpy (hostname, p, p2 - p);
		hostname[p2-p] = '\0';
	} else {
		if (strlen(p) > CA_MAXHOSTNAMELEN)
			return (0);
		strcpy (hostname, p);
	}

	p2 = strrchr (hostname, ':');
	p3 = strchr (hostname, ']');

	if (p2 && p3 && p2<p3)
		p2 = NULL;

	if (p2)
		hostname[p2-hostname] = '\0';

	memset (&hints, '\0', sizeof(hints));
	hints.ai_family = PF_INET6;
	gaierrno = Cgetaddrinfo (hostname, NULL, &hints, &aitop);
	if (gaierrno != 0)
		aitop = NULL;

	ret = (aitop != NULL) ? 1 : 0;

	if (aitop)
		freeaddrinfo (aitop);

	return (ret);
}
