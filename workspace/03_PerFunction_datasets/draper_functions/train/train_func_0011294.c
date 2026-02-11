get_id(nic_t *nic,
		  const char *sysfs_template,
		  const size_t sysfs_template_size, uint32_t *id)
{
	int rc = 0;
	FILE *fp;
	size_t chars_read;
	char buf[7];
	char *path;
	size_t path_size;

	path_size = sysfs_template_size + 4;
	path = malloc(path_size);
	if (path == NULL) {
		LOG_ERR("Could not allocate memory for %s", sysfs_template);
		return -ENOMEM;
	}

	snprintf(path, path_size, sysfs_template, nic->uio_minor);

	fp = fopen(path, "r");
	if (fp == NULL) {
		LOG_ERR(PFX "%s: Could not open path: %s [%s]",
			nic->log_name, path, strerror(errno));
		rc = -EIO;
		goto error_fopen;
	}

	chars_read = fread(buf, sizeof(buf), 1, fp);
	if (chars_read != 1) {
		LOG_ERR(PFX "%s: Could not read from: %s [%s]",
			nic->log_name, path, strerror(ferror(fp)));
		rc = -EIO;
		goto error;
	}

	chars_read = sscanf(buf, "%x", id);
	if (chars_read != 1) {
		LOG_ERR(PFX "%s: Could interpret value: %s from: %s [%s]",
			nic->log_name, buf, path, strerror(errno));
		rc = -EIO;
		goto error;
	}

error:
	fclose(fp);

error_fopen:
	free(path);

	return rc;
}
