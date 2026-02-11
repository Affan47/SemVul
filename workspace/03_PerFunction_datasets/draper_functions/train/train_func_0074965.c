pidfile_open(const char *path, mode_t mode, pid_t *pidptr)
{
	struct pidfh *pfh;
	struct stat sb;
	int error, fd,  count;
	struct timespec rqtp;

	pfh = malloc(sizeof(*pfh));
	if (pfh == NULL)
		return (NULL);

	if (path == NULL) {


			free(pfh);
			return (NULL);

	} else
		pfh->pf_path = strdup(path);


	fd = flopen(pfh->pf_path,
	    O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK, mode);
	if (fd == -1) {
		count = 0;
		rqtp.tv_sec = 0;
		rqtp.tv_nsec = 5000000;
		if (errno == EWOULDBLOCK && pidptr != NULL) {
		again:
			errno = pidfile_read(pfh->pf_path, pidptr);
			if (errno == 0)
				errno = EEXIST;
			else if (errno == EAGAIN) {
				if (++count <= 3) {
					nanosleep(&rqtp, 0);
					goto again;
				}
			}
		}
		free(pfh->pf_path);
		free(pfh);
		return (NULL);
	}


	if (fstat(fd, &sb) == -1) {
		error = errno;
		unlink(pfh->pf_path);
		free(pfh->pf_path);
		close(fd);
		free(pfh);
		errno = error;
		return (NULL);
	}

	pfh->pf_fd = fd;
	pfh->pf_dev = sb.st_dev;
	pfh->pf_ino = sb.st_ino;

	return (pfh);
}
