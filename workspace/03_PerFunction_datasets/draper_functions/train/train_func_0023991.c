popen2(FILE **in, FILE **out, char *command, char *param)
{
	char *argv[3] = { command, param, NULL };
	struct fd_pair infd, outfd;
	pid_t pid;

	xpiped_pair(infd);
	xpiped_pair(outfd);

	fflush_all();
	pid = xvfork();

	if (pid == 0) {


		close(infd.wr);
		close(outfd.rd);
		xmove_fd(infd.rd, 0);
		xmove_fd(outfd.wr, 1);
		BB_EXECVP_or_die(argv);
	}

	close(infd.rd);
	close(outfd.wr);
	*in = xfdopen_for_write(infd.wr);
	*out = xfdopen_for_read(outfd.rd);
	return pid;
}
