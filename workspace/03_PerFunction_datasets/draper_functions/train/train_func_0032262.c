open_pid_file(void)
{
	if (strlen(nhrp_pid_file) == 0)
		return TRUE;

	pid_file_fd = open(nhrp_pid_file, O_CREAT | O_WRONLY,
			   S_IRUSR | S_IWUSR);
	if (pid_file_fd < 0)
		goto err;

	fcntl(pid_file_fd, F_SETFD, FD_CLOEXEC);
	if (flock(pid_file_fd, LOCK_EX | LOCK_NB) < 0)
		goto err_close;

	return TRUE;

err_close:
	close(pid_file_fd);
err:
	nhrp_error("Unable to open/lock pid file: %s.", strerror(errno));
	return FALSE;
}
