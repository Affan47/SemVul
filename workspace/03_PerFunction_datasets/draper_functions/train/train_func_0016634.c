child(fd_t stdfd[3][2], unsigned stdfds, const char *argv[])
{
	int j;
	pid_t pid;

	if (!pipes(stdfd, stdfds))
		return -1;
	fflush(NULL);
	errno = 0;
	if ((pid = fork()) < 0) {
		message("could not fork");
		return -1;
	}

	if (pid)
		return pid;


	for (j = 0; j < 3; j++) {
		close(stdfd[j][0]);
		errno = 0;
		if (dup2(stdfd[j][1], j) != j) {
			fprintf(stderr, "dup2(%d,%d) failed: %s\n",
				stdfd[j][1], j, strerror(errno));
			exit(EXIT_FAILURE);
		}
		close(stdfd[j][1]);
	}

	if (isatty(0)) {
		pid = setsid();
		ioctl(0, TIOCSCTTY);
		ioctl(0, TIOCSPGRP, &pid);
	}
	setenv("TERM", "network", TRUE);
	unsetenv("LS_COLORS");

	errno = 0;
	execvp(argv[0], (char *const *) argv);

	fprintf(stderr, "could not execute %s: %s\n",
		argv[0], strerror(errno));
	exit(EXIT_FAILURE);
}
