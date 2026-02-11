GetHost( bool peername )
{
	CString s,host;
	int port;

	if ( peername )
	{
		if ( !GetPeerName(&host,&port) )
		{
			return s;
		}
	}
	else
	{
		port = GetPort();
		host = GetIP();
	}

	s = host + ':' + CString::number(port);

	return s;
}
