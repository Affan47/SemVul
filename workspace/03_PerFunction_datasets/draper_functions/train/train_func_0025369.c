retry_read(int fd, void *buf0, unsigned nbyte, unsigned delta)
{
    int nr;
    unsigned nleft = nbyte;
    char *buf = (char*) buf0;

    while (nleft >= 1) {
	if (delta > 0) {
	    if (read_wait(fd, delta))
		return -1;
	}
	nr = read(fd, buf, nleft);
	if (nr < 0) {
	    if (errno == EINTR || errno == EAGAIN)
		continue;
	    return -1;
	} else if (nr == 0) {
	    break;
	}
      buf += nr;
      nleft -= nr;
    }
    return nbyte - nleft;
}
