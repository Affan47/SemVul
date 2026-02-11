setup_sideband(int fd[2], int xd[2])
{
	pid_t side_pid;

	if (!use_sideband) {
		fd[0] = xd[0];
		fd[1] = xd[1];
		return 0;
	}


	if (pipe(fd) < 0)
		die("fetch-pack: unable to set up pipe");
	side_pid = fork();
	if (side_pid < 0)
		die("fetch-pack: unable to fork off sideband demultiplexer");
	if (!side_pid) {

		close(fd[0]);
		if (xd[0] != xd[1])
			close(xd[1]);
		if (recv_sideband("fetch-pack", xd[0], fd[1], 2))
			exit(1);
		exit(0);
	}
	close(xd[0]);
	close(fd[1]);
	fd[1] = xd[1];
	return side_pid;
}
