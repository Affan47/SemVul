proc_info_load(void)
{
	DIR *dir;
	struct dirent *dirent;

	if ((dir = opendir("/proc")) == NULL)
		return -1;

	while ((dirent = readdir(dir))) {
		if (isdigit(dirent->d_name[0])) {
			pid_t pid = atoi(dirent->d_name);
			(void)proc_info_add(pid, NULL);
			proc_thread_info_add(pid);
		}
	}

	(void)closedir(dir);
	return 0;
}
