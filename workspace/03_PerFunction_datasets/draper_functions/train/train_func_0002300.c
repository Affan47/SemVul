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
	very_first_event.sec = 0;
	reset_counters();

	print_title();
	lol_create(&lo);
	if (user_file) {
		struct stat sb;
		if (stat(user_file, &sb) == -1) {
			perror("stat");
			return 1;
		} else {
			switch (sb.st_mode & S_IFMT) {
				case S_IFDIR:
					userfile_is_dir = 1;
					rc = process_logs();
					break;
				case S_IFREG:
				default:
					rc = process_file(user_file);
					break;
			}
		}
	} else if (force_logs)
		rc = process_logs();
	else if (is_pipe(0))
		rc = process_stdin();
	else
		rc = process_logs();
	lol_clear(&lo);
	if (rc)
		return rc;

	if (!found && report_detail == D_DETAILED && report_type != RPT_TIME) {
		printf("<no events of interest were found>\n\n");
		destroy_counters();
		aulookup_destroy_uid_list();
		aulookup_destroy_gid_list();
		return 1;
	} else
		print_wrap_up();
	destroy_counters();
	aulookup_destroy_uid_list();
	aulookup_destroy_gid_list();
	free(user_file);
	return 0;
}
