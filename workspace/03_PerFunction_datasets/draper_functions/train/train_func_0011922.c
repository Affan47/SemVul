cmd_upload_archive(int argc, const char **argv, const char *prefix)
{
	pid_t writer;
	int fd1[2], fd2[2];


	if (pipe(fd1) < 0 || pipe(fd2) < 0) {
		int err = errno;
		packet_write(1, "NACK pipe failed on the remote side\n");
		die("upload-archive: %s", strerror(err));
	}
	writer = fork();
	if (writer < 0) {
		int err = errno;
		packet_write(1, "NACK fork failed on the remote side\n");
		die("upload-archive: %s", strerror(err));
	}
	if (!writer) {

		dup2(fd1[1], 1);
		dup2(fd2[1], 2);
		close(fd1[1]); close(fd2[1]);
		close(fd1[0]); close(fd2[0]);

		exit(run_upload_archive(argc, argv, prefix));
	}


	close(fd1[1]); close(fd2[1]);
	packet_write(1, "ACK\n");
	packet_flush(1);

	while (1) {
		struct pollfd pfd[2];
		int status;

		pfd[0].fd = fd1[0];
		pfd[0].events = POLLIN;
		pfd[1].fd = fd2[0];
		pfd[1].events = POLLIN;
		if (poll(pfd, 2, -1) < 0) {
			if (errno != EINTR) {
				error("poll failed resuming: %s",
				      strerror(errno));
				sleep(1);
			}
			continue;
		}
		if (pfd[1].revents & POLLIN)

			if (process_input(pfd[1].fd, 2))
				continue;
		if (pfd[0].revents & POLLIN)

			if (process_input(pfd[0].fd, 1))
				continue;

		if (waitpid(writer, &status, 0) < 0)
			error_clnt("%s", lostchild);
		else if (!WIFEXITED(status) || WEXITSTATUS(status) > 0)
			error_clnt("%s", deadchild);
		packet_flush(1);
		break;
	}
	return 0;
}
