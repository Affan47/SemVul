find_sysfs_devs(void)
{
	char class_path[IBV_SYSFS_PATH_MAX];
	DIR *class_dir;
	struct dirent *dent;
	struct ibv_sysfs_dev *sysfs_dev = NULL;
	char value[8];
	int ret = 0;

	snprintf(class_path, sizeof class_path, "%s/class/infiniband_verbs",
		 ibv_get_sysfs_path());

	class_dir = opendir(class_path);
	if (!class_dir)
		return ENOSYS;

	while ((dent = readdir(class_dir))) {
		struct stat buf;

		if (dent->d_name[0] == '.')
			continue;

		if (!sysfs_dev)
			sysfs_dev = malloc(sizeof *sysfs_dev);
		if (!sysfs_dev) {
			ret = ENOMEM;
			goto out;
		}

		snprintf(sysfs_dev->sysfs_path, sizeof sysfs_dev->sysfs_path,
			 "%s/%s", class_path, dent->d_name);

		if (stat(sysfs_dev->sysfs_path, &buf)) {
			fprintf(stderr, PFX "Warning: couldn't stat '%s'.\n",
				sysfs_dev->sysfs_path);
			continue;
		}

		if (!S_ISDIR(buf.st_mode))
			continue;

		snprintf(sysfs_dev->sysfs_name, sizeof sysfs_dev->sysfs_name,
			"%s", dent->d_name);

		if (ibv_read_sysfs_file(sysfs_dev->sysfs_path, "ibdev",
					sysfs_dev->ibdev_name,
					sizeof sysfs_dev->ibdev_name) < 0) {
			fprintf(stderr, PFX "Warning: no ibdev class attr for '%s'.\n",
				dent->d_name);
			continue;
		}

		snprintf(sysfs_dev->ibdev_path, sizeof sysfs_dev->ibdev_path,
			 "%s/class/infiniband/%s", ibv_get_sysfs_path(),
			 sysfs_dev->ibdev_name);

		sysfs_dev->next        = sysfs_dev_list;
		sysfs_dev->have_driver = 0;
		if (ibv_read_sysfs_file(sysfs_dev->sysfs_path, "abi_version",
					value, sizeof value) > 0)
			sysfs_dev->abi_ver = strtol(value, NULL, 10);
		else
			sysfs_dev->abi_ver = 0;

		sysfs_dev_list = sysfs_dev;
		sysfs_dev      = NULL;
	}

 out:
	if (sysfs_dev)
		free(sysfs_dev);

	closedir(class_dir);
	return ret;
}
