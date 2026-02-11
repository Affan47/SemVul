fd_writeable(slurm_fd_t fd)
{
	struct pollfd ufds;
	int msg_timeout = 5000;
	int rc, time_left;
	struct timeval tstart;
	char temp[2];

	ufds.fd     = fd;
	ufds.events = POLLOUT;
	gettimeofday(&tstart, NULL);
	while (shutdown_time == 0) {
		time_left = msg_timeout - _tot_wait(&tstart);
		rc = poll(&ufds, 1, time_left);
		if (shutdown_time)
			return false;
		if (rc == -1) {
			if ((errno == EINTR) || (errno == EAGAIN))
				continue;
			error("poll: %m");
			return false;
		}
		if (rc == 0) {
			debug2("write timeout");
			return false;
		}


		if (ufds.revents & POLLHUP || (recv(fd, &temp, 1, 0) == 0)) {
			debug3("Write connection %d closed", fd);
			return false;
		}
		if (ufds.revents & POLLNVAL) {
			error("Connection %d is invalid", fd);
			return false;
		}
		if (ufds.revents & POLLERR) {
			error("Connection %d experienced an error", fd);
			return false;
		}
		if ((ufds.revents & POLLOUT) == 0) {
			error("Connection %d events %d", fd, ufds.revents);
			return false;
		}
		break;
	}
	errno = 0;
	return true;
}
