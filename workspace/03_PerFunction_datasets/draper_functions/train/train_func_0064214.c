print_run_info(FILE * log_fp, int argc, char **argv)
{
	time_t time_run;
	int i;

	time_run = time(0);
	fprintf(log_fp, "\n# ");
	for (i = 0; i < argc; i++)
		fprintf(log_fp, " %s ", argv[i]);
	fprintf(log_fp, "\n#\tVersion %s, %d thread(s) starting at %s",
		fs_mark_version, num_threads, ctime(&time_run));
	fprintf(log_fp, "#\tSync method: %s\n",
		sync_policy_string[sync_method_type]);
	if (num_subdirs > 1) {
		fprintf(log_fp,
			"#\tDirectories:  %s across %d subdirectories with %d %s.\n",
			dir_policy_string[dir_policy], num_subdirs,
			dir_policy ==
			DIR_ROUND_ROBIN ? num_per_subdir : (int) secs_per_directory,
			dir_policy == DIR_ROUND_ROBIN ? "files per subdirectory" :
			"seconds per subdirectory");
	} else
		fprintf(log_fp, "#\tDirectories:  no subdirectories used\n");
	fprintf(log_fp,
		"#\tFile names: %d bytes long, (%d initial bytes of time stamp with %d random bytes at end of name)\n",
		name_len, name_len - rand_len, rand_len);
	fprintf(log_fp,
		"#\tFiles info: size %d bytes, written with an IO size of %d bytes per write\n",
		file_size, io_buffer_size);
	fprintf(log_fp,
		"#\tApp overhead is time in microseconds spent in the test not doing file writing related system calls.\n");

	if (log_fp != stdout)
		fprintf(log_fp, "#");
	if (verbose_stats) {
		fprintf(log_fp,
			"#\tAll system call times are reported in microseconds.\n\n");
		fprintf(log_fp,
			"%6s %12s %12s %12s %16s %26s %26s %26s %26s %26s %26s\n",
			"FSUse%", "Count", "Size", "Files/sec", "App Overhead",
			"CREAT (Min/Avg/Max)", "WRITE (Min/Avg/Max)",
			"FSYNC (Min/Avg/Max)", "SYNC (Min/Avg/Max)",
			"CLOSE (Min/Avg/Max)", "UNLINK (Min/Avg/Max)");
	} else {
		fprintf(log_fp, "\n");
		fprintf(log_fp, "%6s %12s %12s %12s %16s\n",
			"FSUse%", "Count", "Size", "Files/sec", "App Overhead");
	}

	return;
}
