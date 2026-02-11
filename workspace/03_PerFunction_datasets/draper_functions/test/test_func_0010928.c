tops_preinput_proc(int x)
{
	char	c;
	char	buf[80];
	int	i,cntx;
        if (debug == 2) { printf(" Entered static void tops_preinput_proc...\n");}

	cntx=read(ttyfd, &buf, 80);
	for (i=0; i < cntx; i++)
	{
		c=buf[i];
		if (c==exit_char)
		{
			ct_reset_term();
			printf("\n\nControl returned to local host.\n");
			close(sockfd);
			exit(1);
		}
	}
	if (write(sockfd, buf, cntx) < 0)
	{
		if (errno == ENOTCONN)
			printf("\n\nControl returned to local host.\n");
		else
			perror("terminal input data message");
		ct_reset_term();
		exit(-1);
	}
}
