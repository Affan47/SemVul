gitno_extract_host_and_port(char **host, char **port, const char *url, const char *default_port)
{
	char *colon, *slash, *delim;

	colon = strchr(url, ':');
	slash = strchr(url, '/');

	if (slash == NULL) {
		giterr_set(GITERR_NET, "Malformed URL: missing /");
		return -1;
	}

	if (colon == NULL) {
		*port = git__strdup(default_port);
	} else {
		*port = git__strndup(colon + 1, slash - colon - 1);
	}
	GITERR_CHECK_ALLOC(*port);

	delim = colon == NULL ? slash : colon;
	*host = git__strndup(url, delim - url);
	GITERR_CHECK_ALLOC(*host);

	return 0;
}
