fdIsSocket(int fd) {
	int ret = fcntl(fd, F_GETFL);
	if (ret == -1) {
		if (errno == EBADF) {
			return FISR_NO;
		} else {
			return FISR_ERROR;
		}
	} else {
		struct stat buf;
		ret = fstat(fd, &buf);
		if (ret == -1) {


			return FISR_YES;
		} else {
			if (buf.st_mode & S_IFSOCK) {
				return FISR_YES;
			} else {
				return FISR_NO;
			}
		}
	}
}
