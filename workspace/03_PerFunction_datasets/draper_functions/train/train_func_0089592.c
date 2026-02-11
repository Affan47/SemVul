liosattach(FILE *stream, int4 node, int4 tfd, int buffering)
{
	int		iofd;
	char		*iosock;
	int4		data[3];


	iosock = lam_get_iosockname();
	if (iosock == 0) return(LAMERROR);

	iofd = sfh_sock_open_clt_unix_stm(iosock);
	free(iosock);
	if (iofd < 0) return(LAMERROR);


	data[0] = node;
	data[1] = tfd;
	data[2] = 0;

	if (mwrite(iofd, (char *) data, sizeof(data)) != sizeof(data)) {
		close(iofd);
		return(LAMERROR);
	}


	if (freopen("/dev/null", "a", stream) == NULL) {
		close(iofd);
		return(LAMERROR);
	}

	if (setvbuf(stream, NULL, buffering, BUFSIZ)) {
		return(LAMERROR);
	}

	if (dup2(iofd, fileno(stream)) < 0) {
		close(iofd);
		return(LAMERROR);
	}

	return(0);
}
