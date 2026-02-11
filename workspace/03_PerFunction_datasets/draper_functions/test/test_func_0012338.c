growl_tcp_parse_hostname( const char *const server , int default_port , struct sockaddr_in *const sockaddr )
{
	char *hostname = strdup(server);
	char *port = strchr( hostname, ':' );
	struct hostent* host_ent;
	if( port != NULL )
	{
		*port = '\0';
		port++;
		default_port = atoi(port);
	}

	host_ent = gethostbyname(hostname);
	if( host_ent == NULL )
	{
		perror("gethostbyname");
		free(hostname);
		return -1;
	}

	memset( sockaddr , 0 , sizeof(sockaddr) );
	sockaddr->sin_family = AF_INET;
	memcpy( &sockaddr->sin_addr , host_ent->h_addr , host_ent->h_length );
	sockaddr->sin_port = htons(default_port);

	free(hostname);
	return 0;
}
