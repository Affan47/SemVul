main(int argc, char *argv[])
{
	struct rlimit limit;
	int rc;


	setlocale (LC_ALL, "");
	if (check_params(argc, argv))
		return 1;


	limit.rlim_cur = RLIM_INFINITY;
	limit.rlim_max = RLIM_INFINITY;
	setrlimit(RLIMIT_FSIZE, &limit);
	setrlimit(RLIMIT_CPU, &limit);
	set_aumessage_mode(MSG_STDERR, DBG_NO);
	(void) umask( umask( 077 ) | 027 );

	lol_create(&lo);
	if (user_file)
		rc = process_file(user_file);
	else if (force_logs)
		rc = process_logs();
	else if (is_pipe(0))
		rc = process_stdin();
	else
		rc = process_logs();
	lol_clear(&lo);
	ilist_clear(event_type);
	free(event_type);
	free(user_file);
	free((char *)event_key);
	auparse_destroy(NULL);
	if (rc)
		return rc;
	if (!found) {
		if (report_format != RPT_RAW)
			fprintf(stderr, "<no matches>\n");
		return 1;
	}
	return 0;
}
