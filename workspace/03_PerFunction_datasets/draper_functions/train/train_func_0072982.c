pushout(int sockfd, char * buf, int buflen)
{
	int	outb;

	while  (buflen > 0)  {
		alarm(output_timeout);
		if  ((outb = write(sockfd, buf, buflen)) < 0)  {
			if  (errno == EINTR)  {
				fprintf(stderr, "Output timeout\n");
				return  1;
			}
			fprintf(stderr, "Lost connection to remote\n");
			cleanupfiles(0);
			exit(40);
		}
		alarm(0);
		buflen -= outb;
		buf += outb;
	}
	return  0;
}
