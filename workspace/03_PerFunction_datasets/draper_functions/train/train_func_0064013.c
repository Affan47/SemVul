Accept(int priv)
{
    int	newsock;

    while (1)
    {
	newsock = accept(sock, (struct sockaddr *)0, (GETPEERNAME_LENGTH_T *)0);
	if (newsock == NOTOK && errno == EINTR)
	    continue;
	break;
    }
    if (newsock == NOTOK)
	return (Connection *)0;

    Connection	*newconnect = new Connection;
    newconnect->sock = newsock;

    GETPEERNAME_LENGTH_T length = sizeof(newconnect->server);
    getpeername(newsock, (struct sockaddr *)&newconnect->server, &length);

    if (priv && newconnect->server.sin_port >= IPPORT_RESERVED)
    {
	delete newconnect;
	return (Connection *)0;
    }

    return newconnect;
}
