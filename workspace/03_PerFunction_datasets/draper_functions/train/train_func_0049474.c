pullin(const int sock, char *cbufp, unsigned ibytes)
{
	int	xbytes;

	while  (ibytes != 0)  {
		if  ((xbytes = read(sock, cbufp, ibytes)) < 0)  {
			if  (errno == EINTR)
				continue;
			abort_exit(0);
		}
		cbufp += xbytes;
		ibytes -= xbytes;
	}
}
