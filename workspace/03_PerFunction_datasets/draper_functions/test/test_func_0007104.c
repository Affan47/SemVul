name_to_dev_t_real(const char *name)
{
	char *p;
	dev_t res = 0;
	char *s;
	int part;
	struct stat st;
	int len;
	const char *devname;
	char *cptr, *e1, *e2;
	int major_num, minor_num;


	if (strchr(name, ','))
		return Root_MULTI;

	if (name[0] == '/') {
		devname = name;
	} else {
		char *dname = alloca(strlen(name) + 6);
		sprintf(dname, "/dev/%s", name);
		devname = dname;
	}

	if (!stat(devname, &st) && S_ISBLK(st.st_mode))
		return st.st_rdev;

	if (strncmp(name, "/dev/", 5)) {
		cptr = strchr(devname+5, ':');
		if (cptr && cptr[1] != '\0') {

			*cptr = '\0';
			major_num = strtoul(devname+5, &e1, 10);
			minor_num = strtoul(cptr+1, &e2, 10);
			if (!*e1 && !*e2)
				return makedev(major_num, minor_num);
			*cptr = ':';
		} else {

			res = (dev_t) strtoul(name, &p, 16);
			if (!*p)
				return res;
		}
	} else {
		name += 5;
	}

	if (!strcmp(name, "nfs"))
		return Root_NFS;

	if (!strcmp(name, "ram"))
		return Root_RAM0;

	if (!strncmp(name, "mtd", 3))
		return Root_MTD;

	len = strlen(name);
	s = alloca(len + 1);
	memcpy(s, name, len + 1);

	for (p = s; *p; p++)
		if (*p == '/')
			*p = '!';
	res = try_name(s, 0);
	if (res)
		return res;

	while (p > s && isdigit(p[-1]))
		p--;
	if (p == s || !*p || *p == '0')
		goto fail;
	part = strtoul(p, NULL, 10);
	*p = '\0';
	res = try_name(s, part);
	if (res)
		return res;

	if (p < s + 2 || !isdigit(p[-2]) || p[-1] != 'p')
		goto fail;
	p[-1] = '\0';
	res = try_name(s, part);
	return res;

fail:
	return (dev_t) 0;
}
