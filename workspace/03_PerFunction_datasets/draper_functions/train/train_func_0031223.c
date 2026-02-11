init_socket()
{
	BOOL result = false;
	bzero(&m_ipaddr,sizeof(m_ipaddr));
	m_ipaddr.sin_family 	=	AF_INET;
	m_ipaddr.sin_port	= 	htons(m_port);
	if ( inet_aton(m_strip,(struct in_addr *)&m_ipaddr.sin_addr.s_addr) == 0 )
	{
		perror("Can't Init a local socket!");
		return result;
	}

	m_socketfd = socket(AF_INET,SOCK_STREAM,0);
	if ( m_socketfd == -1 ) { return false; }

	result = true;
	return result;
}
