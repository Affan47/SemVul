child(struct argstruct *threadargs){
	int sockfd = threadargs->sockfd;

	printf("CHILD: initial socket id: %d\n", sockfd);
	fflush(stdout);


	if(listen(sockfd, 5)){
		perror("CHILD: The listen() call returned with an error ");
	}else{
		printf("CHILD: listen succeeded\n");
	}


	if(close(sockfd)){
		perror("CHILD: The close() call returned with an error ");
	}else{
		printf("CHILD: close succeeded\n");
	}


	char cbuf[10];
	cbuf[0] = 'a';
	if(write(threadargs->pfds[WRITE_END], &cbuf, 1) != 1){
		fprintf(stderr, "CHILD: write to pipe failed\n");
		fflush(stderr);
	}


	int childsockfd = socket(AF_FINS, SOCK_MODE, PF_FINS);
	printf("CHILD: secondary socket id: %d\n", childsockfd);
	fflush(stdout);


	if(listen(childsockfd, 5)){
		perror("CHILD: The listen() call returned with an error ");
	}else{
		printf("CHILD: listen succeeded\n");
	}

	pthread_exit(NULL);
}
