sis190_phy_timer(unsigned long __opaque)
{
	struct net_device *dev = (struct net_device *)__opaque;
	struct sis190_private *tp = netdev_priv(dev);

	if (likely(netif_running(dev)))
		schedule_work(&tp->phy_task);
}
