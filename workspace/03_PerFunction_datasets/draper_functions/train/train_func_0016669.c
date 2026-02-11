kill_child (pid_t pid, int fd) {
	int status;

	slave_fd = -1;
	alarm_fired = 0;
	if (fd >= 0) {
		close(fd);
	}
	kill(pid, SIGTERM);
	waitpid(pid, &status, WNOHANG);
}
