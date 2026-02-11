netxen_nic_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	u32 wol_cfg = 0;

	wol->supported = 0;
	wol->wolopts = 0;

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG_NV);
	if (wol_cfg & (1UL << adapter->portnum))
		wol->supported |= WAKE_MAGIC;

	wol_cfg = NXRD32(adapter, NETXEN_WOL_CONFIG);
	if (wol_cfg & (1UL << adapter->portnum))
		wol->wolopts |= WAKE_MAGIC;
}
