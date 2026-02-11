fc_xchg_originate ( struct interface *parent, struct fc_port *port,
			struct fc_port_id *peer_port_id, unsigned int type ) {
	struct fc_exchange *xchg;


	xchg = fc_xchg_create ( port, peer_port_id, type );
	if ( ! xchg )
		return -ENOMEM;
	xchg->flags = ( FC_XCHG_ORIGINATOR | FC_XCHG_SEQ_INITIATIVE |
			FC_XCHG_SEQ_FIRST );

	DBGC2 ( port, "FCXCHG %s/%04x originating to %s (type %02x)\n",
		port->name, xchg->xchg_id, fc_id_ntoa ( &xchg->peer_port_id ),
		xchg->type );


	intf_plug_plug ( &xchg->ulp, parent );
	return xchg->xchg_id;
}
