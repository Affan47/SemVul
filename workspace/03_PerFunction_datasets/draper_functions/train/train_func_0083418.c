cm_subproc_mark_most_cloexec(struct cm_store_entry *entry, int fd)
{
	int i;
	long l;
	if (fd != STDIN_FILENO) {
		i = open("/dev/null", O_RDONLY);
		if (i != -1) {
			if (i != STDIN_FILENO) {
				dup2(i, STDIN_FILENO);
				close(i);
			}
		} else {
			close(STDIN_FILENO);
		}
	}
	if (fd != STDOUT_FILENO) {
		i = open("/dev/null", O_WRONLY);
		if (i != -1) {
			if (i != STDOUT_FILENO) {
				dup2(i, STDOUT_FILENO);
				close(i);
			}
		} else {
			close(STDOUT_FILENO);
		}
	}
	if (fd != STDERR_FILENO) {
		i = open("/dev/null", O_WRONLY);
		if (i != -1) {
			if (i != STDERR_FILENO) {
				dup2(i, STDERR_FILENO);
				close(i);
			}
		} else {
			close(STDERR_FILENO);
		}
	}
	for (i = getdtablesize() - 1; i >= 3; i--) {
		if (i == fd) {
			continue;
		}
		l = fcntl(i, F_GETFD);
		if (l != -1) {
			if (fcntl(i, F_SETFD, l | FD_CLOEXEC) != 0) {
				cm_log(0, "Potentially leaking FD %d.\n", i);
			}
		}
	}
}
