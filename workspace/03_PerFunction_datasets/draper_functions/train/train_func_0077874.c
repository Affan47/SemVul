openfile_or_pipe(const char *filename, const char *mode)
{
int	fd;
FILE	*fp;

	if (strcmp(filename, "-") == 0)
		fd=dup( strcmp(mode, "r") ? 1:0);
	else if (*filename == '&')
		fd=dup( atoi(filename+1));
	else fd=open(filename, (strcmp(mode, "r") ? O_WRONLY|O_CREAT|O_TRUNC:
			O_RDONLY), 0666);
	if (fd < 0)
	{
		perror(filename);
		exit(1);
	}
	fp=fdopen(fd, mode);
	if (!fp)
	{
		perror("fdopen");
		exit(1);
	}
	return (fp);
}
