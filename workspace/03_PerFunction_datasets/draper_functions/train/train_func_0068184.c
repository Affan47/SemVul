already_loaded(const char *name)
{
	int ret = 0;
	char *s;
	parser_t *parser = config_open2("/proc/modules", xfopen_for_read);
	while (config_read(parser, &s, 1, 1, "# \t", PARSE_NORMAL & ~PARSE_GREEDY)) {
		if (strcmp(s, name) == 0) {
			ret = 1;
			break;
		}
	}
	config_close(parser);
	return ret;
}
