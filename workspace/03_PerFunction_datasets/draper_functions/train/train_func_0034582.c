daemon_is_running(const char *name)
{
	char *pidfile = NULL;
	int pid_fd;


	if (!name)
		return set_errno(EINVAL);


	if (daemon_construct_pidfile(name, &pidfile) == -1)
		return -1;


	if ((pid_fd = open(pidfile, O_RDONLY)) == -1)
	{
		mem_release(pidfile);

		if (errno != ENOENT)
			return -1;


		return 0;
	}


	if (fcntl_lock(pid_fd, F_SETLK, F_RDLCK, SEEK_SET, 0, 0) == -1)
	{
		mem_release(pidfile);
		close(pid_fd);

		if (errno != EACCES && errno != EAGAIN)
			return -1;

		return 1;
	}

	mem_release(pidfile);
	close(pid_fd);


	return 0;
}
