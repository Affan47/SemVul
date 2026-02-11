last_lba(int fd)
{
	int rc;
	uint64_t sectors = 0;
	struct stat s;

	memset(&s, 0, sizeof (s));
	rc = fstat(fd, &s);
	if (rc == -1)
	{
		fprintf(stderr, "last_lba() could not stat: %s\n",
			strerror(errno));
		return 0;
	}
	if (S_ISBLK(s.st_mode))
		sectors = _get_num_sectors(fd);
	else if (S_ISREG(s.st_mode))
		sectors = s.st_size >> _get_sector_size(fd);
	else
	{
		fprintf(stderr,
			"last_lba(): I don't know how to handle files with mode %o\n",
			s.st_mode);
		sectors = 1;
	}
	return sectors - 1;
}
