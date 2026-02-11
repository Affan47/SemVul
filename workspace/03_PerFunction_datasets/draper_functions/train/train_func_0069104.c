fc_port_demux ( struct fc_port *port,
					    unsigned int xchg_id ) {
	struct fc_exchange *xchg;

	list_for_each_entry ( xchg, &port->xchgs, list ) {
		if ( xchg->xchg_id == xchg_id )
			return xchg;
	}
	return NULL;
}
