http_size( http_t *conn )
{
	char *i;
	long long int j;

	if( ( i = http_header( conn, "Content-Length:" ) ) == NULL )
		return( -2 );

	sscanf( i, "%lld", &j );
	return( j );
}
