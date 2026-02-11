atl1_mii_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	unsigned long flags;
	int retval;

	if (!netif_running(netdev))
		return -EINVAL;

	spin_lock_irqsave(&adapter->lock, flags);
	retval = generic_mii_ioctl(&adapter->mii, if_mii(ifr), cmd, NULL);
	spin_unlock_irqrestore(&adapter->lock, flags);

	return retval;
}
