write_all(int fd, const char *buf, int len) {
	int rv,done=0;

	while (done < len) {
		rv = write(fd, buf+done, len-done);
		if (rv <= 0)
			break;
		done += rv;
	}
	return done;
}
