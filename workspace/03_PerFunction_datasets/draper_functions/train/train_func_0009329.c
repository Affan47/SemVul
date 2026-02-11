startlistening(int port) {

	char myname[MAXHOSTNAME+1];
	int s;
	struct sockaddr_in sa;
	struct hostent *hp;
	memset(&sa, 0, sizeof(struct sockaddr_in));
	gethostname(myname, MAXHOSTNAME);
	if((hp = gethostbyname(myname)) == NULL) {
		return(-1);
	}

	sa.sin_family = hp->h_addrtype;
	sa.sin_port = htons(port);

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return(-1);
	}

	if (bind(s, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) < 0) {
		close(s);
		return(-1);
	}
	listen(s, 1);
	return(s);
}
