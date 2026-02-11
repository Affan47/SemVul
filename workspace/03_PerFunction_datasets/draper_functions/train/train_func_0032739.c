tsend_dgram(int fd, char* buf, unsigned int len,
				const struct sockaddr* to, socklen_t tolen, int timeout)
{
	TSEND_INIT;
again:
	n=sendto(fd, buf, len, 0, to, tolen);
	TSEND_ERR_CHECK("tsend_dgram");


	return n;
	TSEND_POLL("tsend_datagram");
error:
	return -1;
}
