find_pppd(int id, pid_t *pid)
{
	struct dirent *de;
	char  path[PATH_MAX + 1];
	char  dev[10];
	int   empty = 1;
	DIR   *dir;

	dir = opendir(PROC_BASE);
	if (!dir) {
		perror(PROC_BASE);
		return -1;
	}

	sprintf(dev, "rfcomm%d", id);

	*pid = 0;
	while ((de = readdir(dir)) != NULL) {
		empty = 0;
		if (isdigit(de->d_name[0])) {
			sprintf(path, "%s/%s/fd", PROC_BASE, de->d_name);
			if (uses_rfcomm(path, dev)) {
				*pid = atoi(de->d_name);
				break;
			}
		}
	}
	closedir(dir);

	if (empty)
		fprintf(stderr, "%s is empty (not mounted ?)\n", PROC_BASE);

	return *pid != 0;
}
