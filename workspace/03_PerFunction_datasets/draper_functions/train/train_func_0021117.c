fc_peer_get_port_id ( struct fc_port *port,
				       const struct fc_port_id *peer_port_id ){
	struct fc_peer *peer;


	list_for_each_entry ( peer, &fc_peers, list ) {
		if ( ( peer->port == port ) &&
		     ( memcmp ( &peer->port_id, peer_port_id,
				sizeof ( peer->port_id ) ) == 0 ) )
			return fc_peer_get ( peer );
	}


	return NULL;
}
