hns_nic_nway_reset(struct net_device *netdev)
{
	int ret = 0;
	struct hns_nic_priv *priv = netdev_priv(netdev);
	struct phy_device *phy = priv->phy;

	if (netif_running(netdev)) {
		if (phy)
			ret = genphy_restart_aneg(phy);
	}

	return ret;
}
