main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port [string1] [string2] ...\n", argv[0]);
       exit(0);
    }
    if (argc > 8){
	printf("Too many strings to transmit\n");
	exit(0);
    }
    portno = atoi(argv[2]);
    int i = 0;
    for (i = 3; i < argc+1; i++) {

	if (i<argc){
		bzero(buffer,256);
		strcpy(buffer,argv[i]);
		if(strlen(buffer)>12){
			printf("Error: Input larger than 12 bytes\n");
			printf("Skipping Entry: %s\n",argv[i]);
			continue;
		}
	}

    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0){
        	printf("ERROR opening socket\n");
		exit(0);
	}
    	server = gethostbyname(argv[1]);
    	if (server == NULL) {
        	fprintf(stderr,"ERROR, no such host\n");
        	exit(0);
    	}
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	bcopy((char *)server->h_addr,
         	(char *)&serv_addr.sin_addr.s_addr,
         	server->h_length);
    	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
	    printf("ERROR connecting\n");
	    exit(0);
	}
	bzero(buffer,256);


	if (i>=argc)
		strcpy(buffer,"DLE ETX");
	else
		strcpy(buffer,argv[i]);

	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0){
	    printf("ERROR writing to socket\n");
	    exit(0);
	}

	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0){
	    printf("ERROR reading from socket");
	    exit(0);
	}

	if(strcmp(buffer,"Done")==0)
		printf("EnhancedClient: %s\n",buffer);
	else
		printf("EnhancedClient received: %s\n",buffer);
	close(sockfd);
	}
    return 0;
}
