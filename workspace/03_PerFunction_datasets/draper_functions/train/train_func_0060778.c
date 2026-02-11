inet_stosockaddr(char *ip, char *port, struct sockaddr_storage *addr)
{
	void *addr_ip;
	char *cp = ip;

	addr->ss_family = (strchr(ip, ':')) ? AF_INET6 : AF_INET;


	if (strstr(ip, "-")) {
		while (*cp != '-' && *cp != '\0')
			cp++;
		if (*cp == '-')
			*cp = 0;
	} else if (strstr(ip, "/")) {
		while (*cp != '/' && *cp != '\0')
			cp++;
		if (*cp == '/')
			*cp = 0;
	}

	if (addr->ss_family == AF_INET6) {
		struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *) addr;
		if (port)
			addr6->sin6_port = htons(atoi(port));
		addr_ip = &addr6->sin6_addr;
	} else {
		struct sockaddr_in *addr4 = (struct sockaddr_in *) addr;
		if (port)
			addr4->sin_port = htons(atoi(port));
		addr_ip = &addr4->sin_addr;
	}

	if (!inet_pton(addr->ss_family, ip, addr_ip))
		return -1;

	return 0;
}
