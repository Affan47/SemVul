hns_nic_init_phy(struct net_device *ndev, struct hnae_handle *h)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct phy_device *phy_dev = NULL;

	if (!h->phy_node)
		return 0;

	if (h->phy_if != PHY_INTERFACE_MODE_XGMII)
		phy_dev = of_phy_connect(ndev, h->phy_node,
					 hns_nic_adjust_link, 0, h->phy_if);
	else
		phy_dev = of_phy_attach(ndev, h->phy_node, 0, h->phy_if);

	if (unlikely(!phy_dev) || IS_ERR(phy_dev))
		return !phy_dev ? -ENODEV : PTR_ERR(phy_dev);

	phy_dev->supported &= h->if_support;
	phy_dev->advertising = phy_dev->supported;

	if (h->phy_if == PHY_INTERFACE_MODE_XGMII)
		phy_dev->autoneg = false;

	priv->phy = phy_dev;

	return 0;
}
