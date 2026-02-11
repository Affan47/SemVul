ropen(const char * host, unsigned short port) {
	int sck;
	struct hostent * entry;
	struct sockaddr_in addr;
	FILE * fd;
	int usesocks;
	char proxcpy[512 + 1];
	char * p;
	const char * connhost;
	unsigned short connport = 0;

	if(!host || !port) {
		fputs("No host/port given.\n", stderr);
		return NULL;
	}

	connhost = host;
	connport = port;

	usesocks = haskey(& rc, "socks-proxy");
	if(usesocks) {
		strncpy(proxcpy, value(& rc, "socks-proxy"), sizeof(proxcpy) - 1);
		proxcpy[sizeof(proxcpy) - 1] = '\0';
		connhost = proxcpy;
		p = strchr(connhost, ':');
		if(p) {
			*p = '\0';
			connport = atoi(p + 1);
		}
		if(connport == 0)
			connport = 1080;
	}

	debug("connecting to %s:%u\n", connhost, connport);
	if(!(entry = gethostbyname(connhost)) || !entry->h_addr) {
		fprintf(stderr, "%s.\n", hstrerror(h_errno));
		return NULL;
	}

	if(-1 == (sck = socket(PF_INET, SOCK_STREAM, PF_UNSPEC))) {
		fprintf(stderr, "Couldn't create socket. %s.\n", strerror(errno));
		return NULL;
	}

	memset(& addr, 0, sizeof(struct sockaddr_in));
	addr.sin_addr.s_addr = * (unsigned *) entry->h_addr;
	addr.sin_port = htons(connport);
	addr.sin_family = PF_INET;

	if(connect(sck, (struct sockaddr *) & addr, sizeof(struct sockaddr_in))) {
		fprintf(stderr, "Connection to %s:%u failed. %s.\n", connhost, connport, strerror(errno));
		return NULL;
	}

	if(!(fd = fdopen(sck, "w+"))) {
		fprintf(stderr, "Couldn't create file handle. %s.\n", strerror(errno));
		shutdown(sck, SHUT_RDWR);
		close(sck);
	}

	if(usesocks) {
		if(tunnel(fd, host, port) == -1) {
			fshutdown(& fd);
		}
	}

	return fd;
}
