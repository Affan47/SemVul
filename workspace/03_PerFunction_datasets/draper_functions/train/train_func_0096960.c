rocker_carrier_init(const struct rocker_port *rocker_port)
{
	const struct rocker *rocker = rocker_port->rocker;
	u64 link_status = rocker_read64(rocker, PORT_PHYS_LINK_STATUS);
	bool link_up;

	link_up = link_status & (1 << rocker_port->pport);
	if (link_up)
		netif_carrier_on(rocker_port->dev);
	else
		netif_carrier_off(rocker_port->dev);
}
