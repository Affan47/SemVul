main(int argc, char **argv)
{
	struct timeval now;
	const char *x;

	x = getenv("TEST_DATE_NOW");
	if (x) {
		now.tv_sec = atoi(x);
		now.tv_usec = 0;
	}
	else
		gettimeofday(&now, NULL);

	argv++;
	if (!*argv)
		usage(usage_msg);
	if (!strcmp(*argv, "show"))
		show_dates(argv+1, &now);
	else if (!strcmp(*argv, "parse"))
		parse_dates(argv+1, &now);
	else if (!strcmp(*argv, "approxidate"))
		parse_approxidate(argv+1, &now);
	else
		usage(usage_msg);
	return 0;
}
