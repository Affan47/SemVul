team_port_get_rtnl(const struct net_device *dev)
{
	struct team_port *port = rtnl_dereference(dev->rx_handler_data);

	return team_port_exists(dev) ? port : NULL;
}
