o_link(struct Luser *lptr, int ac, char **av, int sockfd)

{
	struct Botlist *bptr;

	if (ac < 2)
	{
		os_notice(lptr, sockfd, "Syntax: \002LINK <botnick>\002");
		return;
	}

	if (!(bptr = IsBot(av[1])))
	{
		os_notice(lptr, sockfd, "No such bot: %s",
		          av[1]);
		return;
	}

	o_RecordCommand(sockfd,
	                "LINK %s",
	                bptr->name);

	os_notice(lptr, sockfd, "Attempting to link to %s",
	          bptr->name);
	os_notice(lptr, sockfd, "Making connection to %s:%d",
	          bptr->hostname,
	          bptr->port);

	ConnectToTCM(onick, bptr);
}
