read_pidfile(const char *pidfile, int *pidfd)
{
	int fd;
	FILE *fp = NULL;
	unsigned long pid;
	pid_t         lpid;

	if ((fd = open(pidfile, O_RDONLY)) < 0)
		return ((pid_t) 0);

	if (!(fp = fdopen(fd, "r")) && (errno != ENOENT))
		error ("Unable to access old pidfile at `%s': %m", pidfile);

	if (fscanf(fp, "%lu", &pid) < 1) {
		error ("Possible corrupt pidfile `%s'", pidfile);
		(void) close(fd);
		return ((pid_t) 0);
	}

	if ((lpid = fd_is_read_lock_blocked(fd)) == (pid_t) 0) {
		verbose ("pidfile not locked, assuming no running daemon");
		(void) close(fd);
		return ((pid_t) 0);
	}

	if (lpid != (pid_t) pid)
		fatal ("pidfile locked by %lu but contains pid=%lu",
		       (unsigned long) lpid, (unsigned long) pid);

	if (pidfd != NULL)
		*pidfd = fd;
	else
		(void) close(fd);

	return (lpid);
}
