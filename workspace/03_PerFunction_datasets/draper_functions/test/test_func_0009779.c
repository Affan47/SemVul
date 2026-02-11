jobok(const jobno_t jobnum, const long jsize, const int cr)
{
	char	*nam;
	struct	stat	sbuf;

	if  (jobnum == 0)
		return  0;
	nam = mkspid(SPNAM, jobnum);
	if  (stat(nam, &sbuf) < 0  ||  sbuf.st_size != jsize)  {
		if  (popts.createmissjobs)  {
			int	fd;
			long	nbytes = 0, towrite;
			char	nbuf[PATH_MAX];
			if  (!cr)
				return  0;
			fprintf(stderr, "Creating missing/incorrect job %ld\n", (long) jobnum);
			sprintf(nbuf, "%s/%s", popts.outdir, nam);
			if  ((fd = open(nbuf, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)  {
				fprintf(stderr, "Sorry couldn't create saved job %s\n", nbuf);
				return  0;
			}
			while  (nbytes < jsize)  {
				towrite = jsize - nbytes;
				if  (towrite > sizeof(misscreate) - 1)
					towrite = sizeof(misscreate) -1;
				write(fd, misscreate, towrite);
				nbytes += towrite;
			}
			close(fd);
			return  1;
		}
		else
			return  0;
	}

	return  1;
}
