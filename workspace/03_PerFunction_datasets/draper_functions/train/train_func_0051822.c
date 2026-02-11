daemon_connect(void)
{
	int sock;
	struct sockaddr_un servaddr;
	char filename[PATH_MAX];
	unsigned char trying=2;

	if ((sock=socket(AF_UNIX,SOCK_STREAM,0)) < 0) {
		perror("Could not create socket\n");
		return -1;
	}
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	sprintf(filename,"%s-%d",SERVER_FILENAME,uid);

	strcpy(servaddr.sun_path,filename);

	while(trying) {
		if ((connect(sock,(struct sockaddr*) &servaddr,
			sizeof(servaddr.sun_family) +
			sizeof(servaddr.sun_path))) >=0)
				goto done;
		printf("The afpfs daemon does not appear to be running for uid %d, let me start it for you\n", uid);

		if (start_afpfsd()!=0) {
			printf("Error in starting up afpfsd\n");
			goto error;
		}
		if ((connect(sock,(struct sockaddr*) &servaddr,
			sizeof(servaddr.sun_family) +
			sizeof(servaddr.sun_path))) >=0)
				goto done;
		sleep(1);
		trying--;
	}
error:
	perror("Trying to startup afpfsd");
	return -1;

done:
	return sock;
}
