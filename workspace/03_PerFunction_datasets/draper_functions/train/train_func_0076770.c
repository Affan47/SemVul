igb_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	if (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE))
		return -EOPNOTSUPP;

	if (!(adapter->flags & IGB_FLAG_WOL_SUPPORTED))
		return wol->wolopts ? -EOPNOTSUPP : 0;


	adapter->wol = 0;

	if (wol->wolopts & WAKE_UCAST)
		adapter->wol |= E1000_WUFC_EX;
	if (wol->wolopts & WAKE_MCAST)
		adapter->wol |= E1000_WUFC_MC;
	if (wol->wolopts & WAKE_BCAST)
		adapter->wol |= E1000_WUFC_BC;
	if (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= E1000_WUFC_MAG;
	if (wol->wolopts & WAKE_PHY)
		adapter->wol |= E1000_WUFC_LNKC;
	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	return 0;
}
