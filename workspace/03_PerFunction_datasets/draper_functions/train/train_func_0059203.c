pushfile(int sockfd, char *filename)
{
	int	infd, inb;
	long	had = 0;
	char	outbuf[1024];

	if  ((infd = open(filename, O_RDONLY)) < 0)  {
		fprintf(stderr, "Lost file %s??\n", filename);
		cleanupfiles(0);
		exit(41);
	}
	while  ((inb = read(infd, outbuf, sizeof(outbuf))) > 0)  {
		had += inb;
		if  (pushout(sockfd, outbuf, inb))
			return  1;
	}
	if  (nonull  &&  had <= 0)  {
		outbuf[0] = '\0';
		if  (pushout(sockfd, outbuf, 1))
			return  1;
	}
	close(infd);
	return  0;
}
