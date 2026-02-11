init_socket(IRCBot *bot, char *nick, char *server, char *port)
{
	bot->nick = malloc(strlen(nick));
	bot->server = malloc(strlen(server));
	bot->port = malloc(strlen(port));
	strcpy(bot->nick, nick);
	strcpy(bot->server, server);
	strcpy(bot->port, port);
	bot->num_chans = 0;
	memset( &bot->hints, 0, sizeof bot->hints);
	bot->hints.ai_family = AF_UNSPEC;
	bot->hints.ai_socktype = SOCK_STREAM;
	switch(getaddrinfo( bot->server, bot->port, &bot->hints, &bot->res))
	{
		case -2:
			fprintf(stderr, "Error: Name or Service not known\n");
			return -2;
		case -3:
			fprintf(stderr, "Error: Temporary failure in name resolution\n");
			return -3;
		case -4:
			fprintf(stderr, "Error: Failure in name resolution\n");
			return -4;
		case -11:
			fprintf(stderr, "System returned error %i\n", errno);
			return errno;
	}


	bot->sock = socket(bot->res->ai_family, bot->res->ai_socktype, bot->res->ai_protocol);
	printf("Attempting to connect to %s:%s\n", bot->server, bot->port);
	if(connect(bot->sock, bot->res->ai_addr, bot->res->ai_addrlen) != -1)  {

		printf("Connected!\n");
	} else {

		fprintf(stderr, "Error: %i\n", errno);
		return errno;
	}
	return 0;
}
