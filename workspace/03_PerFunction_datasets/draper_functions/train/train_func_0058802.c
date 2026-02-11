net80211_netdev_irq ( struct net_device *netdev, int enable )
{
	struct net80211_device *dev = netdev->priv;

	if ( dev->op->irq )
		dev->op->irq ( dev, enable );
}
