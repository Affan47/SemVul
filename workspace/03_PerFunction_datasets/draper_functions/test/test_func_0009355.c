qlcnic_set_features(struct net_device *netdev, netdev_features_t features)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = netdev->features ^ features;
	int hw_lro = (features & NETIF_F_LRO) ? QLCNIC_LRO_ENABLED : 0;

	if (!(changed & NETIF_F_LRO))
		return 0;

	netdev->features ^= NETIF_F_LRO;

	if (qlcnic_config_hw_lro(adapter, hw_lro))
		return -EIO;

	if (!hw_lro && qlcnic_82xx_check(adapter)) {
		if (qlcnic_send_lro_cleanup(adapter))
			return -EIO;
	}

	return 0;
}
