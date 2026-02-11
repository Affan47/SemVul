main(int argc, char **argv)
{
	int i;
	int persistent=0;
	int listen_fd=-1;
	int parameters=0;
	struct hostent *hp;
	char *host=DEFHOST;
	char *port=DEFPORT;
	char *localport=LOCALPORT;

	for (i=1;i<argc;i++) {
		if (argv[i][0]=='-') {
			if (!strcmp(argv[i],"-persistent")) {
	persistent=1;
			} else if (!strcmp(argv[i],"-debug")) {
	debug=1;
			} else if (!strcmp(argv[i],"-help")) {
	printf("hub [options] [host [remoteport [localport]]]\n\
Options: -help         this page\n\
         -persistent   hub remains alive after last client exits\n\
         -debug        hub prints lots of useless info while working\n\
         -mirror       mirror data from all other clients\n");
	exit(0);
      } else if (!strcmp(argv[i],"-mirror")) {
	mirror=1;
      } else {
	printf("unkown option: %s\n",argv[i]);
      }
    } else {
	switch (parameters) {
	case 0: host=argv[i]; break;
	case 1: port=argv[i]; break;
	case 2: localport=argv[i]; break;
	default: fprintf(stderr,"Unknown argument: %s\n",argv[i]);
	}
	parameters++;
    }
  }

	if (isdigit(*host)) {
		sock_in.sin_addr.s_addr = inet_addr(host);
	} else {
		hp = gethostbyname(host);
		if (!hp) {
			printf("%s: No such host\n", host);
			return -errno;
		}
		memcpy( &sock_in.sin_addr, hp->h_addr, sizeof(sock_in.sin_addr));
	}
	sock_in.sin_port = htons(atoi(port));
	sock_in.sin_family = AF_INET;


	listen_fd = open_listen(atoi(localport));


	do {
		while (main_loop(listen_fd)>0) {}

	} while (persistent);

	close(listen_fd);
	return 0;
}
