pfs_paranoia_cleanup(void)
{
	if(paranoia_mode == 0)
		return -1;

	int ret;
	char value = 'A';

	while(-1 == (ret = write(to_watchdog_fd, &value, 1))) {
		if(errno == EINTR) {
			continue;
		} else if((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
			continue;
		} else {

			return 1;
		}
	}

	munmap(shared_table, (max_pids + 1) / sizeof(pid_t));
	shared_table = NULL;


	int status = 0;
	pid_t result = waitpid(watchdog_pid, &status, 0);
	if(result < 0) {

		return 1;
	}

	return 0;
}
