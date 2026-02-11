getsubj(char *subj)
{
	pid_t pid = getpid();
	char filename[48];
	ssize_t num_read;
	int fd;

	snprintf(filename, sizeof(filename), "/proc/%u/attr/current", pid);
	fd = open(filename, O_RDONLY);
	if(fd == -1) {
		subj[0] = 0;
		return NULL;
	}
	do {
		num_read = read(fd, subj, SUBJ_LEN-1);
	} while (num_read < 0 && errno == EINTR);
	close(fd);
	if(num_read <= 0) {
		subj[0] = 0;
		return NULL;
	}
	subj[num_read] = '\0';
	return subj;
}
