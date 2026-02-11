tsend_dgram_ev(int fd, const struct iovec* v, int count, int timeout)
{
	TSEND_INIT;
again:
	n=writev(fd, v, count);
	TSEND_ERR_CHECK("tsend_datagram_ev");
	return n;
	TSEND_POLL("tsend_datagram_ev");
error:
	return -1;
}
