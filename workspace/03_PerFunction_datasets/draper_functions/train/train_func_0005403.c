fcntl_unlock_file(int lockfd)
{
	struct flock lock = {
		.l_type = F_UNLCK,
		.l_whence = 0,
		.l_start = 0,
		.l_len = 0
	};

	log_very_verbose("Unlocking fd %d", lockfd);

	if (fcntl(lockfd, F_SETLK, &lock) == -1)
		log_error("fcntl unlock failed on fd %d: %s", lockfd,
			  strerror(errno));

	if (close(lockfd))
		log_error("lock file close failed on fd %d: %s", lockfd,
			  strerror(errno));
}
