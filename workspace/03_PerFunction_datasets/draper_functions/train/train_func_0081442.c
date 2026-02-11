maildir_tmpcreate_fp(struct maildir_tmpcreate_info *info)
{
	int fd=maildir_tmpcreate_fd(info);
	FILE *fp;

	if (fd < 0)
		return NULL;

	fp=fdopen(fd, "w+");

	if (fp == NULL)
	{
		close(fd);
		return NULL;
	}

	return fp;
}
