CopyFile(char *oldfile, char *newfile)

{
	int oldfd, newfd, ret, bytes;
	struct stat fst;
	char buffer[MAXLINE + 1];

	if ((oldfd = open(oldfile, O_RDONLY, 0)) < 0)
		return (-1);

	ret = fstat(oldfd, &fst);
	if (ret == -1)
	{
		close(oldfd);
		return -3;
	}

	if (!(fst.st_mode & S_IFREG))
	{
		close(oldfd);
		return (-3);
	}

	if ((newfd = creat(newfile, (int) (fst.st_mode & 0700))) < 0)
	{
		close(oldfd);
		return (-2);
	}


	for (bytes = 1; bytes > 0; )
	{
		bytes = read(oldfd, buffer, sizeof(buffer));
		if (bytes > 0)
		{
			if (write(newfd, buffer, bytes) < bytes)
			{

				close(oldfd);
				close(newfd);
				unlink(newfile);
				return (-4);
			}
		}


	}


	close(oldfd);
	close(newfd);
	return (0);
}
