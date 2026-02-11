isit_r23(const int ifd, const struct stat *sb)
{
	struct	spptr	old;

	if  ((sb->st_size % sizeof(struct spptr)) != 0  &&  (!popts.ignsize  ||  ++popts.errors > popts.errtol))
		return  0;

	lseek(ifd, 0L, 0);

	while  (read(ifd, (char *) &old, sizeof(old)) == sizeof(old))
		if  (!fldsok23(&old)  &&  (!popts.ignfmt  ||  ++popts.errors > popts.errtol))
			return  0;
	return  1;
}
