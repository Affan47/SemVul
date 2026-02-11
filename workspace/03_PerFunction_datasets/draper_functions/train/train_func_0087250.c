exec_umount(const char *progname, const char *rel_mnt, int lazy)
{
	int res;
	int status;
	sigset_t blockmask;
	sigset_t oldmask;

	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGCHLD);
	res = sigprocmask(SIG_BLOCK, &blockmask, &oldmask);
	if (res == -1) {
		fprintf(stderr, "%s: sigprocmask: %s\n", progname, strerror(errno));
		return -1;
	}

	res = fork();
	if (res == -1) {
		fprintf(stderr, "%s: fork: %s\n", progname, strerror(errno));
		goto out_restore;
	}
	if (res == 0) {
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
		setuid(geteuid());
		execl("/bin/umount", "/bin/umount", "-i", rel_mnt,
		      lazy ? "-l" : NULL, NULL);
		fprintf(stderr, "%s: failed to execute /bin/umount: %s\n",
			progname, strerror(errno));
		exit(1);
	}
	res = waitpid(res, &status, 0);
	if (res == -1)
		fprintf(stderr, "%s: waitpid: %s\n", progname, strerror(errno));

	if (status != 0) {
		res = -1;
	}

 out_restore:
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return res;

}
