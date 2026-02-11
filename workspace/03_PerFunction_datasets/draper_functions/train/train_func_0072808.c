update_total_processes(void)
{
	DIR *dir;
	struct dirent *entry;
	int ignore1;
	char ignore2;

	info.procs = 0;
	if (!(dir = opendir("/proc"))) {
		return 0;
	}
	while ((entry = readdir(dir))) {
		if (!entry) {

			closedir(dir);
			info.procs = 0;
			return 0;
		}
		if (sscanf(entry->d_name, "%d%c", &ignore1, &ignore2) == 1) {
			info.procs++;
		}
	}
	closedir(dir);
	return 0;
}
