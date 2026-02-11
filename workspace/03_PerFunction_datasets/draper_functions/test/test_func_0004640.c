rocker_port_change_mtu(struct net_device *dev, int new_mtu)
{
	struct rocker_port *rocker_port = netdev_priv(dev);
	int running = netif_running(dev);
	int err;

#define ROCKER_PORT_MIN_MTU	68
#define ROCKER_PORT_MAX_MTU	9000

	if (new_mtu < ROCKER_PORT_MIN_MTU || new_mtu > ROCKER_PORT_MAX_MTU)
		return -EINVAL;

	if (running)
		rocker_port_stop(dev);

	netdev_info(dev, "MTU change from %d to %d\n", dev->mtu, new_mtu);
	dev->mtu = new_mtu;

	err = rocker_cmd_set_port_settings_mtu(rocker_port, new_mtu);
	if (err)
		return err;

	if (running)
		err = rocker_port_open(dev);

	return err;
}
