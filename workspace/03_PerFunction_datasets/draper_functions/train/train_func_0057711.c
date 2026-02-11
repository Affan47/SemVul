sky2_nway_reset(struct net_device *dev)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	if (!netif_running(dev) || !(sky2->flags & SKY2_FLAG_AUTO_SPEED))
		return -EINVAL;

	sky2_phy_reinit(sky2);
	sky2_set_multicast(dev);

	return 0;
}
