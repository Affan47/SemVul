__agg_active_ports(struct aggregator *agg)
{
	struct port *port;
	int active = 0;

	for (port = agg->lag_ports; port;
	     port = port->next_port_in_aggregator) {
		if (port->is_enabled)
			active++;
	}

	return active;
}
