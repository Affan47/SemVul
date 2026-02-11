__set_agg_ports_ready(struct aggregator *aggregator, int val)
{
	struct port *port;

	for (port = aggregator->lag_ports; port;
	     port = port->next_port_in_aggregator) {
		if (val)
			port->sm_vars |= AD_PORT_READY;
		else
			port->sm_vars &= ~AD_PORT_READY;
	}
}
