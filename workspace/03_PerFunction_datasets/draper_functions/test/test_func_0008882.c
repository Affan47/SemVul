readn(int fd, char *buf, int bufsize, ioTunnel *en)
{
	int             nleft, nread;

	nleft = bufsize;

	while (nleft > 0) {

#ifdef WIN32
		nread = recv(fd, buf, nleft, 0);
#else
		nread = en == NULL ? system_read(fd, buf, nleft) : en->eRead(fd, buf, nleft);
#endif

		if (nread < 0)
			return (nread);
		else if (nread == 0)
			break;
		nleft -= nread;
		buf += nread;
	}

	return (bufsize - nleft);
}
