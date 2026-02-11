argsread(char *argvname)
{
	char		*args;
	int		avfd;
	struct stat	avstat;

	if (stat(argvname, &avstat)) return(0);

	args = malloc((unsigned int) avstat.st_size);
	if (args == 0) lampanic("kenyad (malloc)");

	avfd = open(argvname, O_RDONLY, 0);

	if (avfd < 0) {
		free(args);
		return(0);
	}

	if (read(avfd, args, (int) avstat.st_size) < 0) {
		free(args);
		close(avfd);
		return(0);
	}

	close(avfd);
	return(args);
}
