_mounted_fs_on_device(const char *kernel_dev_name)
{
	char sysfs_path[PATH_MAX];
	struct dirent *dirent;
	DIR *d;
	struct stat st;
	int r = 0;

	if (dm_snprintf(sysfs_path, PATH_MAX, "%sfs", _sysfs_dir) < 0) {
		log_error("sysfs_path dm_snprintf failed");
		return 0;
	}

	if (!(d = opendir(sysfs_path))) {
		if (errno != ENOENT)
			log_sys_error("opendir", sysfs_path);
		return 0;
	}

	while ((dirent = readdir(d))) {
		if (!strcmp(dirent->d_name, ".") || !strcmp(dirent->d_name, ".."))
			continue;

		if (dm_snprintf(sysfs_path, PATH_MAX, "%sfs/%s/%s",
				_sysfs_dir, dirent->d_name, kernel_dev_name) < 0) {
			log_error("sysfs_path dm_snprintf failed");
			break;
		}

		if (!stat(sysfs_path, &st)) {

			r = 1;
			break;
		}
		else if (errno != ENOENT) {
			log_sys_error("stat", sysfs_path);
			break;
		}
	}

	if (closedir(d))
		log_error("_fs_present_on_device: %s: closedir failed", kernel_dev_name);

	return r;
}
