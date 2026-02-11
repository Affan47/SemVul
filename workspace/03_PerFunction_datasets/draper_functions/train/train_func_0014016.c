core_uses_pid(void)
{
	const char *	uses_pid_pathnames[] = {PROC_SYS_KERNEL_CORE_PID};
	const char *	corepats_pathnames[] = {PROC_SYS_KERNEL_CORE_PAT};
	const char *	goodpats [] = {"%t", "%p"};
	int		j;


	for (j=0; j < DIMOF(corepats_pathnames); ++j) {
		int	fd;
		char	buf[BUF_MAX];
		int	rc;
		int	k;

		if ((fd = open(corepats_pathnames[j], O_RDONLY)) < 0) {
			continue;
		}

		memset(buf, 0, BUF_MAX);
		rc = read(fd, buf, BUF_MAX - 1);
		close(fd);

		for (k=0; rc > 0 && k < DIMOF(goodpats); ++k) {
			if (strstr(buf, goodpats[k]) != NULL) {
				return 1;
			}
		}

		break;
	}
	for (j=0; j < DIMOF(uses_pid_pathnames); ++j) {
		int	fd;
		char	buf[2];
		int	rc;
		if ((fd = open(uses_pid_pathnames[j], O_RDONLY)) < 0) {
			continue;
		}
		rc = read(fd, buf, sizeof(buf));
		close(fd);
		if (rc < 1) {
			continue;
		}
		return (buf[0] == '1');
	}
	setenv(CHECKED_KERNEL_CORE_ENV, "1", TRUE);
	return -1;
}
