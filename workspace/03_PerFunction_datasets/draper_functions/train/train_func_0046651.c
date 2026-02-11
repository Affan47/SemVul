httpclose(uh, fd)
int uh, fd;
{
	char buf[BUFSIZ];
	int n;

	if (!(urlhostlist[uh].http)) return(seterrno(EINVAL));
	if (!(urlhostlist[uh].fp)) return(0);

	n = 0;
	if (((urlhostlist[uh].http) -> flags & HFL_CLENGTH)) {
		while ((urlhostlist[uh].http) -> clength > (off_t)0) {
			if ((urlhostlist[uh].http) -> clength > MAXFLUSH)
				break;
			n = checkread(fd, buf, sizeof(buf), URLENDTIMEOUT);
			if (n <= 0) break;
			(urlhostlist[uh].http) -> clength -= (off_t)n;
		}
		if ((urlhostlist[uh].http) -> clength > (off_t)0) {
			safefclose(urlhostlist[uh].fp);
			urlhostlist[uh].fp = NULL;
		}
	}
	httpflush(uh);

	return(n);
}
