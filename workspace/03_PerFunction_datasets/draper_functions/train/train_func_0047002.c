tester_uri( char *uri, char *host, int port )
{
	static char	uribuf[ BUFSIZ ];

	if ( uri != NULL ) {
		return uri;
	}

	snprintf( uribuf, sizeof( uribuf ), "ldap://%s:%d", host, port );

	return uribuf;
}
