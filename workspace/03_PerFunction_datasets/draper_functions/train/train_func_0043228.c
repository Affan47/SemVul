_shepard_notify(int shepard_fd)
{
	int rc;

	while (1) {
		rc = write(shepard_fd, "", 1);
		if (rc == -1) {
			if ((errno == EAGAIN) || (errno == EINTR))
				continue;
			error("write(shepard): %m");
		}
		break;
	}
	close(shepard_fd);
}
