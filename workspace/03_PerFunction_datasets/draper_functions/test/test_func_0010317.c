main(int argc, char *argv[])
{
	do
		if (strcmp(argv[argc - 1], "-v") == 0 ||
		    strcmp(argv[argc - 1], "--verbose") == 0)
			debug = 1;
		else if (strcmp(argv[argc - 1], "-b") == 0 ||
			 strcmp(argv[argc - 1], "--break-on-error") == 0)
			break_on_error = 1;
		else if (strcmp(argv[argc - 1], "-h") == 0 ||
			 strcmp(argv[argc - 1], "-?") == 0 ||
			 strcmp(argv[argc - 1], "--help") == 0) {
			printf
			    ("Usage: %s [-vbh?] [--verbose] [--break-on-error] [--help]\n",
			     argv[0]);
			return 1;
		}
	while (argc-- > 1);

	doit();

	if (debug || error_count > 0)
		printf("Self test `%s' finished with %d errors\n", argv[0],
		       error_count);

	return error_count ? 1 : 0;
}
