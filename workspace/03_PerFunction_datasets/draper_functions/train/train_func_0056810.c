ipv6_sock_aton ( const char *string, struct sockaddr *sa ) {
	struct sockaddr_in6 *sin6 = ( ( struct sockaddr_in6 * ) sa );
	struct in6_addr in;
	struct net_device *netdev;
	size_t len;
	char *tmp;
	char *in_string;
	char *netdev_string;
	int rc;


	tmp = strdup ( string );
	if ( ! tmp ) {
		rc = -ENOMEM;
		goto err_alloc;
	}
	in_string = tmp;


	len = strlen ( in_string );
	if ( ( in_string[0] == '[' ) && ( in_string[ len - 1 ] == ']' ) ) {
		in_string[ len - 1 ] = '\0';
		in_string++;
	}


	netdev_string = strchr ( in_string, '%' );
	if ( netdev_string )
		*(netdev_string++) = '\0';


	if ( ( rc = inet6_aton ( in_string, &in ) ) != 0 )
		goto err_inet6_aton;


	if ( netdev_string ) {
		netdev = find_netdev ( netdev_string );
		if ( ! netdev ) {
			rc = -ENODEV;
			goto err_find_netdev;
		}
		sin6->sin6_scope_id = netdev->index;
	}


	memcpy ( &sin6->sin6_addr, &in, sizeof ( sin6->sin6_addr ) );

 err_find_netdev:
 err_inet6_aton:
	free ( tmp );
 err_alloc:
	return rc;
}
