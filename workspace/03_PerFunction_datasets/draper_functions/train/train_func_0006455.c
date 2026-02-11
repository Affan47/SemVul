readfat(devp)
devstat *devp;
{
	long size;
	int duperrno;

	duperrno = errno;
	size = (long)(devp -> fatsize) * (long)(devp -> sectsize);
	if (size > MAXFATMEM) devp -> fatbuf = NULL;
	else if ((devp -> fatbuf = (char *)malloc(size))
	&& sectread(devp, devp -> fatofs,
	(u_char *)(devp -> fatbuf), devp -> fatsize) < 0L) {
		doserrno = errno;
		free(devp -> fatbuf);
		errno = duperrno;
		return(-1);
	}
	errno = duperrno;

	return(0);
}
