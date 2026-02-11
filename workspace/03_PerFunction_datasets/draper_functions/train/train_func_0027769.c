feed_pr(const jobno_t jobno, const char *prefix, const int sock)
{
	int	ffd, bytes;
	char	buffer[1024];

	if  ((ffd = open(mkspid(prefix, jobno), O_RDONLY)) >= 0)  {
		while  ((bytes = read(ffd, buffer, sizeof(buffer))) > 0)
			sockwrite(sock, buffer, bytes);
		close(ffd);
	}
}
