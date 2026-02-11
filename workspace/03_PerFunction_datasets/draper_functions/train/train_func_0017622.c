noproxy_for_host(const char * noproxy_domains, const char * host) {

	char * s;
	char * nd;

	if (noproxy_domains == NULL)
		return 0;

	nd = strdup(noproxy_domains);
	s = strtok(nd, ",");
	while (s != NULL) {
		char * str = strip_whitespace(s);
		if (strstr(host, str) != NULL) {
#ifdef HTTPC_DEBUG
			printf("%s matches %s, no proxy.\n", str, host);
#endif
			free(nd);
			return 1;
		}
		s = strtok(NULL, ",");
	}

	free(nd);
	return 0;
}
