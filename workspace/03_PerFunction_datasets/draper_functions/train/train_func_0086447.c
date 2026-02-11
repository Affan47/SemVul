autodetect_devices ()
{
	int num_devices = 0;
	DIR *dp;
	struct dirent *ep;
	dp = opendir(SYSFS_BLOCK);
	if (dp != NULL) {
		while ((ep = readdir(dp))) {
			char path[FILENAME_MAX];
			char removable[FILENAME_MAX];
			snprintf(removable, sizeof(removable), REMOVABLE_FMT, ep->d_name);

			if (kernel_interface == UNLOAD_HEADS)
				snprintf(path, sizeof(path), UNLOAD_HEADS_FMT, ep->d_name);
			else
				snprintf(path, sizeof(path), QUEUE_PROTECT_FMT, ep->d_name);

			if (access(path, F_OK) == 0 && read_int(removable) == 0 && read_int(path) >= 0) {
				printlog(stdout, "Adding autodetected device: %s", ep->d_name);
				add_disk(ep->d_name);
				num_devices++;
			}
		}
		(void)closedir(dp);
	}
	return num_devices;
}
