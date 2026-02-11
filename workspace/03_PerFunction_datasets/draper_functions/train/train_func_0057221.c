clar_parse_args(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; ++i) {
		char *argument = argv[i];

		if (argument[0] != '-')
			clar_usage(argv[0]);

		switch (argument[1]) {
		case 's': {
			int num = (int)strtol(argument + 2, &argument, 10);
			if (argument == argv[i] + 2) {
				size_t j;
				num = -1;
				for (j = 0; j < _clar_suite_count; ++j)
					if (strcmp(argument, _clar_suites[j].name) == 0) {
						num = j;
						break;
					}
			}
			if (num < 0)
				clar_usage(argv[0]);
			if ((size_t)num >= _clar_suite_count) {
				clar_print_onabort("Suite number %d does not exist.\n", num);
				exit(-1);
			}
			clar_run_suite(&_clar_suites[num]);
			break;
		}

		case 'q':
			_clar.report_errors_only = 1;
			break;

		default:
			clar_usage(argv[0]);
		}
	}
}
