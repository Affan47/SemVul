parse_options(char *options)
{
	char		*p;
	substring_t	args[MAX_OPT_ARGS];
	int		option;

	if (!options)
		return;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_kmsg_bytes:
			if (!match_int(&args[0], &option))
				pstore_set_kmsg_bytes(option);
			break;
		}
	}
}
