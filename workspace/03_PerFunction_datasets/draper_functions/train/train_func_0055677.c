http_parse_proto(char *pstr) {
	char		*pver, *dotptr, *endptr;
	int		major, minor;


	if (strncasecmp(pstr, "HTTP", 4) != 0)
		return HP_UNKNOWN;

	pver=strchr(pstr, '/');
	if (!pver)
		return HP_HTTP;

	major=strtol(++pver, &dotptr, 10);


	if (*dotptr != '.')
		return HP_HTTP;

	minor=strtol(++dotptr, &endptr, 10);


	if (*endptr != 0x0)
		return HP_HTTP;

	Dprintf("%s: major %d minor %d\n", __FUNCTION__, major, minor);

	if (major == 1 && minor == 0)
		return HP_HTTP10;
	if (major == 1 && minor == 1)
		return HP_HTTP11;

	return HP_HTTP;
}
