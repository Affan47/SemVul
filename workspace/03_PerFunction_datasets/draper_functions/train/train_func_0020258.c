update_uptime(void)
{
#ifdef HAVE_SYSINFO
	if (!prefer_proc) {
		struct sysinfo s_info;

		sysinfo(&s_info);
		info.uptime = (double) s_info.uptime;
	} else
#endif
	{
		static int rep = 0;
		FILE *fp;

		if (!(fp = open_file("/proc/uptime", &rep))) {
			info.uptime = 0.0;
			return 0;
		}
		fscanf(fp, "%lf", &info.uptime);
		fclose(fp);
	}
	return 0;
}
