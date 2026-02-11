mktmpfile(int input, Dir **sb)
{
	int fd, i;
	char *p;
	char buf[8192];

	atnotify(catch, 1);


	fd = mkstemp(p=tmp[whichtmp++]);
	if (fd < 0) {
		panic(mflag ? 0: 2, "cannot create %s: %r\n", p);
		return 0;
	}
	while ((i = read(input, buf, sizeof(buf))) > 0) {
		if ((i = write(fd, buf, i)) < 0)
			break;
	}
	*sb = dirfstat(fd);
	close(fd);
	if (i < 0) {
		panic(mflag ? 0: 2, "cannot read/write %s: %r\n", p);
		return 0;
	}
	return p;
}
