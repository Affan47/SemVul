peer_arp( peer *p ) {
    gchar ip[16], hw[18];
    FILE *arp;

    g_assert( p != NULL );

    arp = fopen( "/proc/net/arp", "r" );
    if ( arp == NULL )
	g_error( "Can't open /proc/net/arp: %m" );

    fscanf(arp, "%*s %*s %*s %*s %*s %*s %*s %*s %*s");
    while (fscanf( arp, "%15s %*s %*s %17s %*s %*s\n", ip, hw ) != EOF)  {
	if ( strncmp( p->ip, ip, sizeof(p->ip) ) == 0 ) {
	    g_strncpy( p->hw, hw, sizeof(p->hw) );
	    break;
	}
    }

    fclose( arp );
    return ( p->hw[0] != '\0' ? p->hw : NULL );
}
