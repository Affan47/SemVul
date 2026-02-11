explore_numeric_scope(pai, hostname, servname, res)
	const struct addrinfo *pai;
	const char *hostname;
	const char *servname;
	struct addrinfo **res;
{
#ifndef SCOPE_DELIMITER
	return explore_numeric(pai, hostname, servname, res);
#else
	const struct afd *afd;
	struct addrinfo *cur;
	int error;
	char *cp, *hostname2 = NULL, *scope, *addr;
	struct sockaddr_in6 *sin6;

	afd = find_afd(pai->ai_family);
	if (afd == NULL)
		return 0;

	if (!afd->a_scoped)
		return explore_numeric(pai, hostname, servname, res);

	cp = strchr(hostname, SCOPE_DELIMITER);
	if (cp == NULL)
		return explore_numeric(pai, hostname, servname, res);


	hostname2 = strdup(hostname);
	if (hostname2 == NULL)
		return EAI_MEMORY;

	hostname2[cp - hostname] = '\0';
	addr = hostname2;
	scope = cp + 1;

	error = explore_numeric(pai, addr, servname, res);
	if (error == 0) {
		u_int32_t scopeid = 0;

		for (cur = *res; cur; cur = cur->ai_next) {
			if (cur->ai_family != AF_INET6)
				continue;
			sin6 = (struct sockaddr_in6 *)(void *)cur->ai_addr;
			if (!ip6_str2scopeid(scope, sin6, &scopeid)) {
				free(hostname2);
				return(EAI_NONAME);
			}
#ifdef HAVE_SIN6_SCOPE_ID
			sin6->sin6_scope_id = scopeid;
#endif
		}
	}

	free(hostname2);

	return error;
#endif
}
