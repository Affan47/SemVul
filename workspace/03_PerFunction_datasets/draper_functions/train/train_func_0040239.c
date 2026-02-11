tlan_phy_print(struct net_device *dev)
{
	struct tlan_priv *priv = netdev_priv(dev);
	u16 i, data0, data1, data2, data3, phy;

	phy = priv->phy[priv->phy_num];

	if (priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY) {
		netdev_info(dev, "Unmanaged PHY\n");
	} else if (phy <= TLAN_PHY_MAX_ADDR) {
		netdev_info(dev, "PHY 0x%02x\n", phy);
		pr_info("   Off.  +0     +1     +2     +3\n");
		for (i = 0; i < 0x20; i += 4) {
			tlan_mii_read_reg(dev, phy, i, &data0);
			tlan_mii_read_reg(dev, phy, i + 1, &data1);
			tlan_mii_read_reg(dev, phy, i + 2, &data2);
			tlan_mii_read_reg(dev, phy, i + 3, &data3);
			pr_info("   0x%02x 0x%04hx 0x%04hx 0x%04hx 0x%04hx\n",
				i, data0, data1, data2, data3);
		}
	} else {
		netdev_info(dev, "Invalid PHY\n");
	}

}
