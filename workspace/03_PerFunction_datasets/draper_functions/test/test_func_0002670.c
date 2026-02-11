parse_loop_device_name(const char *dev, const char *dev_dir)
{
	char *buf;
	char *device = NULL;

	if (!(buf = dm_malloc(PATH_MAX)))
		return NULL;

	if (dev[0] == '/') {
		if (!(device = _get_abspath(dev)))
			goto error;

		if (strncmp(device, dev_dir, strlen(dev_dir)))
			goto error;


		if (dev_dir[strlen(dev_dir) - 1] != '/' &&
		    device[strlen(dev_dir)] != '/')
			goto error;

		strncpy(buf, strrchr(device, '/') + 1, PATH_MAX - 1);
		buf[PATH_MAX - 1] = '\0';
		dm_free(device);

	} else {

		if (!strncmp(dev, "loop", strlen("loop")))
			strncpy(buf, dev, (size_t) PATH_MAX);
		else
			goto error;
	}

	return buf;

error:
	dm_free(device);
	dm_free(buf);

	return NULL;
}
