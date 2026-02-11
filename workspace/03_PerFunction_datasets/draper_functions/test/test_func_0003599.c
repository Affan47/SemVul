list_devs_in_proc_partititons(void)
{
	FILE *procpt;
	char line[100], ptname[100], devname[120], *s;
	int ma, mi, sz;

	procpt = fopen_or_warn("/proc/partitions", "r");

	while (fgets(line, sizeof(line), procpt)) {
		if (sscanf(line, " %u %u %u %[^\n ]",
				&ma, &mi, &sz, ptname) != 4)
			continue;
		for (s = ptname; *s; s++)
			continue;

		if (s[-1] >= '1' && s[-1] <= '9')
			continue;
		sprintf(devname, "/dev/%s", ptname);
		open_list_and_close(devname, 0);
	}
#if ENABLE_FEATURE_CLEAN_UP
	fclose(procpt);
#endif
}
