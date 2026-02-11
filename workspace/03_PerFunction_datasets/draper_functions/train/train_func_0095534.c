get_primary_dev(const char *sysfs_dir,
		    const struct device *dev, dev_t *result)
{
	char path[PATH_MAX+1];
	char temp_path[PATH_MAX+1];
	char buffer[64];
	struct stat info;
	FILE *fp;
	uint32_t pri_maj, pri_min;
	int size, ret = 0;


	if (dm_snprintf(path, PATH_MAX, "%s/dev/block/%d:%d/partition",
			sysfs_dir, (int)MAJOR(dev->dev), (int)MINOR(dev->dev)) < 0) {
		log_error("dm_snprintf partition failed");
		return ret;
	}

	if (stat(path, &info) == -1) {
		if (errno != ENOENT)
			log_sys_error("stat", path);
		return ret;
	}


	if ((size = readlink(dirname(path), temp_path, PATH_MAX)) < 0) {
		log_sys_error("readlink", path);
		return ret;
	}

	temp_path[size] = '\0';

	if (dm_snprintf(path, PATH_MAX, "%s/block/%s/dev",
			sysfs_dir, basename(dirname(temp_path))) < 0) {
		log_error("dm_snprintf dev failed");
		return ret;
	}


	if (stat(path, &info) == -1) {
		if (errno == ENOENT)
			log_error("sysfs file %s does not exist", path);
		else
			log_sys_error("stat", path);
		return ret;
	}

	fp = fopen(path, "r");
	if (!fp) {
		log_sys_error("fopen", path);
		return ret;
	}

	if (!fgets(buffer, sizeof(buffer), fp)) {
		log_sys_error("fgets", path);
		goto out;
	}

	if (sscanf(buffer, "%d:%d", &pri_maj, &pri_min) != 2) {
		log_error("sysfs file %s not in expected MAJ:MIN format: %s",
			  path, buffer);
		goto out;
	}
	*result = MKDEV((dev_t)pri_maj, pri_min);
	ret = 1;

out:
	if (fclose(fp))
		log_sys_error("fclose", path);

	return ret;
}
