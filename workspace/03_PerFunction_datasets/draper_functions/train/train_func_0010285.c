fc_peer_get_wwn ( const struct fc_name *port_wwn ) {
	struct fc_peer *peer;


	list_for_each_entry ( peer, &fc_peers, list ) {
		if ( memcmp ( &peer->port_wwn, port_wwn,
			      sizeof ( peer->port_wwn ) ) == 0 )
			return fc_peer_get ( peer );
	}


	peer = fc_peer_create ( port_wwn );
	if ( ! peer )
		return NULL;

	return peer;
}
