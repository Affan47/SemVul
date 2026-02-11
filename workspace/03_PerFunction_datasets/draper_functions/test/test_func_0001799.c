sierra_net_get_link(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);

	return sierra_net_get_private(dev)->link_up && netif_running(net);
}
