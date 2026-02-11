_calc_device_major(char *dev_path[PATH_MAX],
				char *dev_major[PATH_MAX],
				int lines)
{

	int k, major, minor;
	char str1[256], str2[256];
	struct stat fs;

	if (lines > PATH_MAX) {
		error("task/cgroup: more devices configured than table size "
		      "(%d > %d)", lines, PATH_MAX);
		lines = PATH_MAX;
	}
	for (k = 0; k < lines; k++) {
		stat(dev_path[k], &fs);
		major = (int)major(fs.st_rdev);
		minor = (int)minor(fs.st_rdev);
		debug3("device : %s major %d, minor %d\n",
			dev_path[k], major, minor);
		if (S_ISBLK(fs.st_mode)) {
			sprintf(str1, "b %d:", major);

		}
		if (S_ISCHR(fs.st_mode)) {
			sprintf(str1, "c %d:", major);

		}
		sprintf(str2, "%d rwm", minor);
		strcat(str1, str2);
		dev_major[k] = xstrdup((char *)str1);
	}
}
