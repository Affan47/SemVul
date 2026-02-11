default_port_for_scheme(const char *scheme_str)
{
	schemes_t *scheme;

	if (scheme_str == NULL)
		return 0;

	for (scheme = schemes; scheme->name != NULL; ++scheme)
		if (strcasecmp(scheme_str, scheme->name) == 0)
			return scheme->default_port;

	return 0;
}
