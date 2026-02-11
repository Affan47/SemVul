finalize(char *tempdir, const char *prog)
{


	FILE *header_fp = xfopen("header", "w");

	if (prog)
		fprintf(header_fp, "profile.process = %s\n", prog);

	fputs("version = "BC_VERSION_STR"\n", header_fp);
	if (ENABLE_FEATURE_BOOTCHARTD_BLOATED_HEADER) {
		char *hostname;
		char *kcmdline;
		time_t t;
		struct tm tm_time;

		char date_buf[sizeof("Mon Jun 21 05:29:03 CEST 2010") * 2];
		struct utsname unamebuf;

		hostname = safe_gethostname();
		time(&t);
		localtime_r(&t, &tm_time);
		strftime(date_buf, sizeof(date_buf), "%a %b %e %H:%M:%S %Z %Y", &tm_time);
		fprintf(header_fp, "title = Boot chart for %s (%s)\n", hostname, date_buf);
		if (ENABLE_FEATURE_CLEAN_UP)
			free(hostname);

		uname(&unamebuf);

		fprintf(header_fp, "system.uname = %s %s %s %s\n",
				unamebuf.sysname,
				unamebuf.release,
				unamebuf.version,
				unamebuf.machine
		);


		kcmdline = xmalloc_open_read_close("/proc/cmdline", NULL);

		fprintf(header_fp, "system.kernel.options = %s", kcmdline);
		if (ENABLE_FEATURE_CLEAN_UP)
			free(kcmdline);
	}
	fclose(header_fp);


	system("tar -zcf /var/log/bootchart.tgz header *.log");

	if (tempdir) {
		unlink("header");
		unlink("proc_stat.log");
		unlink("proc_diskstats.log");

		unlink("proc_ps.log");
		rmdir(tempdir);
	}


}
