add_server(const char *opt)
{
	struct rad_server_t *s = _malloc(sizeof(*s));

	memset(s, 0, sizeof(*s));

	if (!parse_server1(opt,s))
		goto add;

	if (!parse_server2(opt,s))
		goto add;

	log_emerg("radius: failed to parse '%s'\n", opt);
	_free(s);
	return;

add:
	__add_server(s);
}
