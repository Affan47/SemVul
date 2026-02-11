maybe_reopen_log_files(const char *log_fname, const char *debug_fname)
{
	static TIME_T last_stat_time;

	if (log_file.fp || debug_file.fp) {
		TIME_T now = time(NULL);
		if (now - last_stat_time > 59) {


			maybe_close_log_file(log_fname, &log_file);
			maybe_close_log_file(debug_fname, &debug_file);
			last_stat_time = now;
		}
	}

	if (log_fname && !log_file.fp)
		open_log_file(log_fname, &log_file);

	if (debug_fname && !debug_file.fp)
		open_log_file(debug_fname, &debug_file);
}
