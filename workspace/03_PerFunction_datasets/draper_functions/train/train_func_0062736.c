fc_port_open ( struct interface *transport, const struct fc_name *node_wwn,
		   const struct fc_name *port_wwn, const char *name ) {
	struct fc_port *port;


	port = zalloc ( sizeof ( *port ) );
	if ( ! port )
		return -ENOMEM;
	ref_init ( &port->refcnt, NULL );
	intf_init ( &port->transport, &fc_port_transport_desc, &port->refcnt );
	fc_link_init ( &port->link, fc_port_examine, &port->refcnt );
	intf_init ( &port->flogi, &fc_port_flogi_desc, &port->refcnt );
	intf_init ( &port->ns_plogi, &fc_port_ns_plogi_desc, &port->refcnt );
	list_add_tail ( &port->list, &fc_ports );
	INIT_LIST_HEAD ( &port->xchgs );
	memcpy ( &port->node_wwn, node_wwn, sizeof ( port->node_wwn ) );
	memcpy ( &port->port_wwn, port_wwn, sizeof ( port->port_wwn ) );
	snprintf ( port->name, sizeof ( port->name ), "%s", name );

	DBGC ( port, "FCPORT %s opened as %s",
	       port->name, fc_ntoa ( &port->node_wwn ) );
	DBGC ( port, " port %s\n", fc_ntoa ( &port->port_wwn ) );


	intf_plug_plug ( &port->transport, transport );
	ref_put ( &port->refcnt );
	return 0;
}
