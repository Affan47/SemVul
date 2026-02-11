_cmdline_parse(int argc, char *argv[])
{
	int opt, opt_index = -1;
	status_t status = STATUS_SUCCESS;

	do {
		opt = getopt_long(argc, argv, shortopt, longopt, &opt_index);
		if (opt == -1)
			break;
		switch (opt) {
		case 0:
			switch (opt_index) {
			case OPT_ALL:
				verbose = VERB_ALL;
				break;
			case OPT_DEBUG:
				verbose = VERB_DEBUG;
				break;
			case OPT_ERROR:
				verbose = VERB_ERROR;
				break;
			case OPT_INFO:
				verbose = VERB_INFO;
				break;
			case OPT_QUIET:
				verbose = VERB_QUIET;
				break;
			case OPT_WARNING:
				verbose = VERB_WARN;
				break;
			}
			break;
		case 'l':
			status = _set_log_path(optarg);
			break;
		case 't':
			status = _set_sleep_interval(optarg);
			break;
		case 'c':
			status = _set_config_path(optarg);
			break;
		case 'v':
			_ledmon_version();
			exit(EXIT_SUCCESS);
		case 'h':
			_ledmon_help();
			exit(EXIT_SUCCESS);
		case ':':
		case '?':
		default:
			log_debug("[opt='%c', opt_index=%d]", opt, opt_index);
			break;
		}
		opt_index = -1;
		if (status != STATUS_SUCCESS)
			return status;
	} while (1);

	return STATUS_SUCCESS;
}
