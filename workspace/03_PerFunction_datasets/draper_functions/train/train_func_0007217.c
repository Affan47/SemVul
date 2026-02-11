o_jump(struct Luser *lptr, int ac, char **av, int sockfd)

{
	int port, tempsock;
	struct Servlist *temp;

	if (ac < 2)
	{
		os_notice(lptr, sockfd,
		          "Syntax: \002JUMP {server} [port]\002");
		return;
	}

	for (temp = ServList; temp; temp = temp->next)
		if (match(av[1], temp->hostname))
			break;

	if (!temp)
	{
		os_notice(lptr, sockfd,
		          "[\002%s\002] is an invalid hub server",
		          av[1]);
		return;
	}

	if (ac >= 3)
	{
		if (!(port = IsNum(av[2])))
		{
			os_notice(lptr, sockfd, "Invalid port [\002%s\002]",
			          av[2]);
			return;
		}
	}
	else
		port = temp->port;

	o_RecordCommand(sockfd,
	                "JUMP %s %d",
	                temp->hostname,
	                port);

	o_Wallops("JUMP %s %d",
	          temp->hostname,
	          port);


	if ((tempsock = ConnectHost(temp->hostname, port)) >= 0)
	{


		toserv(":%s ERROR :Rerouting\r\n", Me.name);
		toserv(":%s QUIT\r\n", Me.name);


		close(HubSock);
		ClearUsers();
		ClearChans();
		ClearServs();

		ClearHashes(0);

		HubSock = tempsock;

		currenthub->connect_ts = 0;
		temp->connect_ts = current_ts;
		currenthub = temp;


		signon();
	}
	else
	{
		os_notice(lptr, sockfd,
		          "Unable to connect to port \002%d\002 of \002%s\002: %s",
		          port,
		          temp->hostname,
		          strerror(errno));
		return;
	}
}
