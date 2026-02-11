sanei_udp_recvfrom(int fd, u_char * buf, int count, char **fromp)
{
	ssize_t l;
	socklen_t fl;
	struct sockaddr_in from;

	fl = sizeof(from);

	l = recvfrom(fd, buf, count, 0, (struct sockaddr *) &from, &fl);

	if (l > 0 && fromp) {
		*fromp = inet_ntoa(from.sin_addr);
	}

	return l;
}
