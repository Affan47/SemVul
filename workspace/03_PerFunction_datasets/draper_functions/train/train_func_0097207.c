fc_port_window_changed ( struct fc_port *port ) {
	size_t window;


	window = xfer_window ( &port->transport );
	if ( window > 0 ) {


		if ( ! fc_link_ok ( &port->link ) )
			fc_link_start ( &port->link );

	} else {


		fc_port_logout ( port, -ENOTCONN );
		fc_link_stop ( &port->link );
	}
}
