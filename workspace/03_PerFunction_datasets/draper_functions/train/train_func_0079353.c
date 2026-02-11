readAll(int fd) {
	string result;
	char buf[1024 * 32];
	ssize_t ret;
	while (true) {
		do {
			ret = read(fd, buf, sizeof(buf));
		} while (ret == -1 && errno == EINTR);
		if (ret == 0) {
			break;
		} else if (ret == -1) {
			if (errno == ECONNRESET) {
				break;
			} else {
				int e = errno;
				throw SystemException("Cannot read from file descriptor", e);
			}
		} else {
			result.append(buf, ret);
		}
	}
	return result;
}
