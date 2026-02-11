be_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct device *dev = &adapter->pdev->dev;

	if (new_mtu < BE_MIN_MTU || new_mtu > BE_MAX_MTU) {
		dev_info(dev, "MTU must be between %d and %d bytes\n",
			 BE_MIN_MTU, BE_MAX_MTU);
		return -EINVAL;
	}

	dev_info(dev, "MTU changed from %d to %d bytes\n",
		 netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;
	return 0;
}
