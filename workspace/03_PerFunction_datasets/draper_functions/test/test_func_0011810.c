parse_long_opt(const char *opt, const char **argv,
		   const char **optarg)
{
	const char *arg = argv[0];
	if (arg[0] != '-' || arg[1] != '-')
		return 0;
	arg += strlen("--");
	if (prefixcmp(arg, opt))
		return 0;
	arg += strlen(opt);
	if (*arg == '=') {
		*optarg = arg + 1;
		return 1;
	}
	if (*arg != '\0')
		return 0;

	if (!argv[1])
		die("Option '--%s' requires a value", opt);
	*optarg = argv[1];
	return 2;
}
