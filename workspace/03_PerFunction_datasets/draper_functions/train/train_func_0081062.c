get_port_number (const char *envname, const char *portname, int defaultport)
{
    struct servent *s;
    char *port_s;

    if (envname && (port_s = getenv (envname)))
    {
	int port = atoi (port_s);
	if (port <= 0)
	{
	    error (0, 0, "%s must be a positive integer!  If you", envname);
	    error (0, 0, "are trying to force a connection via rsh, please");
	    error (0, 0, "put \":server:\" at the beginning of your CVSROOT");
	    error (1, 0, "variable.");
	}
	return port;
    }
    else if (portname && (s = getservbyname (portname, "tcp")))
	return ntohs (s->s_port);
    else
	return defaultport;
}
