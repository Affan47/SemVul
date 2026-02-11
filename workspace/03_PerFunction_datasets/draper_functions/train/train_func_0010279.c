parse_bool(struct mkfs_opts *opts, const char *key, const char *val)
{
	if (strnlen(val, 2) == 1) {
		if (*val == '0')
			return 0;
		if (*val == '1')
			return 1;
	}
	fprintf(stderr, _("Option '%s' must be either 1 or 0\n"), key);
	exit(-1);
}
