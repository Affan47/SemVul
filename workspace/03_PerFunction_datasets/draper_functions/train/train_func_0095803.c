writeall(int fd, char* buf, int count)
{
	int origcount = count;
	while (count > 0) {
		int n = write(fd, buf, count);
		if (n < 0) return n;
		count -= n;
		buf += n;
	}

	return origcount;
}
