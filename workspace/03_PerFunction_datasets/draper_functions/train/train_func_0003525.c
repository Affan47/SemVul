skge_nway_reset(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);

	if (skge->autoneg != AUTONEG_ENABLE || !netif_running(dev))
		return -EINVAL;

	skge_phy_reset(skge);
	return 0;
}
