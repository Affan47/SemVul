bus_to_host(char *bus)
{
	int i, nr, host = -1;
	char path[PATH_MAX], *p;
	char key[] = "host";
	struct dirent **namelist;

	p = strchr(bus, ',');
	if (!p)
		return -EINVAL;
	*(p++) = '\0';

	snprintf(path, sizeof(path), "/sys/bus/%s/devices/%s", bus, p);
	nr = scandir(path, &namelist, filter, alphasort);
	if (!nr)
		return -ENOENT;

	for (i = 0; i < nr; i++) {
		if (strncmp(namelist[i]->d_name, key, strlen(key)))
			continue;
		p = namelist[i]->d_name + strlen(key);
		host = strtoull(p, NULL, 10);
	}

	for (i = 0; i < nr; i++)
		free(namelist[i]);
	free(namelist);

	if (host == -1) {
		eprintf("can't find bus: %s\n", bus);
		exit(EINVAL);
	}
	return host;
}
