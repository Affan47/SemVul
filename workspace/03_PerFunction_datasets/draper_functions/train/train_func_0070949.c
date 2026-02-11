tell()
{
	if (fd_ < 0)	return (0);

off_t	p=mseek(fd_, 0L, SEEK_CUR);

	if (p == -1)	return (-1);
	return (p + (writeptr - buf) - readcnt);
}
