evemu_read(struct evemu_device *dev, FILE *fp)
{
	int rc = -1;
	struct version file_version;
	size_t size = 0;
	char *line = NULL;
	char *name = NULL;

	if (strlen(evemu_get_name(dev)) > 0)
		name = strdup(evemu_get_name(dev));
	memset(dev, 0, sizeof(*dev));
	dev->version = EVEMU_VERSION;
	if (name) {
		evemu_set_name(dev, name);
		free(name);
	}


	if (!first_line(fp, &line, &size)) {
		error(WARNING, "This appears to be an empty file\n");
		return -1;
	}

	file_version = parse_file_format_version(line);

	if (is_comment(line) && !next_line(fp, &line, &size)) {
		error(WARNING, "This appears to be an empty file\n");
		goto out;
	}

	if (!parse_name(dev, line, &file_version))
		goto out;

	if (!next_line(fp, &line, &size))
		goto out;

	if (!parse_bus_vid_pid_ver(dev, line, &file_version))
		goto out;


	if (!next_line(fp, &line, &size)) {
		rc = 1;
		goto out;
	}

	while((rc = parse_prop(dev, line, &file_version)) > 0)
		if (!next_line(fp, &line, &size))
			break;
	if (rc == -1)
		goto out;

	while((rc = parse_mask(dev, line, &file_version)) > 0)
		if (!next_line(fp, &line, &size))
			break;
	if (rc == -1)
		goto out;

	while((rc = parse_abs(dev, line, &file_version)) > 0)
		if (!next_line(fp, &line, &size))
			break;
	if (rc == -1)
		goto out;

	rc = 1;

out:
	free(line);
	return rc;
}
