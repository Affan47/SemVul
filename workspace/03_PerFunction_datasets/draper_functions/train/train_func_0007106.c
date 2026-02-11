hostfromaddr(lwres_gnbaresponse_t *addr, int af, const void *src) {
	struct hostent *he;
	int i;

	he = malloc(sizeof(*he));
	if (he == NULL)
		goto cleanup;
	memset(he, 0, sizeof(*he));


	he->h_addrtype = af;
	switch (af) {
	case AF_INET:
		he->h_length = INADDRSZ;
		break;
	case AF_INET6:
		he->h_length = IN6ADDRSZ;
		break;
	default:
		INSIST(0);
	}


	he->h_name = strdup(addr->realname);
	if (he->h_name == NULL)
		goto cleanup;


	he->h_aliases = malloc(sizeof(char *) * (addr->naliases + 1));
	if (he->h_aliases == NULL)
		goto cleanup;
	for (i = 0; i < addr->naliases; i++) {
		he->h_aliases[i] = strdup(addr->aliases[i]);
		if (he->h_aliases[i] == NULL)
			goto cleanup;
	}
	he->h_aliases[i] = NULL;


	he->h_addr_list = malloc(sizeof(char *) * 2);
	if (he->h_addr_list == NULL)
		goto cleanup;
	he->h_addr_list[0] = malloc(he->h_length);
	if (he->h_addr_list[0] == NULL)
		goto cleanup;
	memmove(he->h_addr_list[0], src, he->h_length);
	he->h_addr_list[1] = NULL;
	return (he);

 cleanup:
	if (he != NULL && he->h_addr_list != NULL) {
		for (i = 0; he->h_addr_list[i] != NULL; i++)
			free(he->h_addr_list[i]);
		free(he->h_addr_list);
	}
	if (he != NULL && he->h_aliases != NULL) {
		for (i = 0; he->h_aliases[i] != NULL; i++)
			free(he->h_aliases[i]);
		free(he->h_aliases);
	}
	if (he != NULL && he->h_name != NULL)
		free(he->h_name);
	if (he != NULL)
		free(he);
	return (NULL);
}
