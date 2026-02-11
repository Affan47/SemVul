cmd_addserver()
{
	int	port;
	char	*p;

	context;
	if(!cmdinfo.isparam)
	{
		say("Usage: addserver <servername> [port]");
		sayf(2,0,"Add a server to the serverlist.");
		return;
	}

	context;
	if(!cmdinfo.istok2)
	{
		port = DEFAULT_PORT;
		p = strchr(cmdinfo.tok1,':');
		if(p != NULL)
		{

			*p = 0;
			port = atoi(p+1);
		}
	}
	else
		port = atoi(cmdinfo.tok2);

	context;
	Server_addserver(cmdinfo.tok1,port);

	sayf(0,0,"Server \"%s:%d\" added to serverlist.",cmdinfo.tok1,port);
}
