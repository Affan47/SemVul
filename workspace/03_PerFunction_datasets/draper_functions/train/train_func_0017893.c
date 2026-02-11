connect_unix(aConfItem *aconf, aClient *cptr,
	int *lenp)
{
	static	struct	sockaddr_un	sock;

	if ((cptr->fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	    {
		report_error("Unix domain connect to host %s failed: %s", cptr);
		return NULL;
	    }
	else if (cptr->fd >= MAXCLIENTS)
	    {
		sendto_flag(SCH_NOTICE,
			    "No more connections allowed (%s)", cptr->name);
		return NULL;
	    }

	get_sockhost(cptr, aconf->host);
	strncpyzt(sock.sun_path, aconf->host + 2, sizeof(sock.sun_path));
	sock.sun_family = AF_UNIX;
	*lenp = strlen(sock.sun_path) + 2;

	SetUnixSock(cptr);
	return (struct sockaddr *)&sock;
}
