ctlfile_append_connectioninfofd(int fd, unsigned rcptnum,
		char infotype, const char *info)
{
char	fmtbuf[MAXLONGSIZE+10];
struct iovec iov[4];
char	buf2[2];

	sprintf(fmtbuf, "%c%u ", COMCTLFILE_DELINFO, rcptnum);
	iov[0].iov_base=(caddr_t)fmtbuf;
	iov[0].iov_len=strlen(fmtbuf);

	buf2[0]=infotype;
	buf2[1]=' ';
	iov[1].iov_base=(caddr_t)buf2;
	iov[1].iov_len=2;
	iov[3].iov_base=(caddr_t)"\n";
	iov[3].iov_len=1;

	while (info && *info)
	{
	unsigned	i;

		for (i=0; info[i] && info[i] != '\n'; i++)
			;

		iov[2].iov_base=(caddr_t)info;
		iov[2].iov_len=i;

		if (i && info[i-1] == '\r')	--iov[2].iov_len;
		ctlfile_appendvfd(fd, iov, 4);
		info += i;
		if (*info)	++info;
	}
}
