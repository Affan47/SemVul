cleandir(char *path) {
	isc_dir_t	dir;
	char		fullname[PATH_MAX + 1];
	size_t		l;
	isc_result_t	ret;

	isc_dir_init(&dir);
	ret = isc_dir_open(&dir, path);
	if (ret != ISC_R_SUCCESS) {
		t_info("isc_dir_open(%s) failed %s\n",
		       path, isc_result_totext(ret));
		return;
	}

	while (isc_dir_read(&dir) == ISC_R_SUCCESS) {
		if (!strcmp(dir.entry.name, "."))
			continue;
		if (!strcmp(dir.entry.name, ".."))
			continue;
		(void)strlcpy(fullname, path, sizeof(fullname));
		(void)strlcat(fullname, "/", sizeof(fullname));
		l = strlcat(fullname, dir.entry.name, sizeof(fullname));
		if (l < sizeof(fullname)) {
			if (remove(fullname))
				t_info("remove(%s) failed %d\n", fullname,
				       errno);
		} else
		       t_info("unable to remove '%s/%s': path too long\n",
			      path, dir.entry.name);

	}
	isc_dir_close(&dir);
	if (rmdir(path))
		t_info("rmdir(%s) failed %d\n", path, errno);

	return;
}
