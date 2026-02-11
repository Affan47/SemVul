sis190_set_speed_auto(struct net_device *dev)
{
	struct sis190_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	int phy_id = tp->mii_if.phy_id;
	int val;

	netif_info(tp, link, dev, "Enabling Auto-negotiation\n");

	val = mdio_read(ioaddr, phy_id, MII_ADVERTISE);


	mdio_write(ioaddr, phy_id, MII_ADVERTISE, (val & ADVERTISE_SLCT) |
		   ADVERTISE_100FULL | ADVERTISE_10FULL |
		   ADVERTISE_100HALF | ADVERTISE_10HALF);


	mdio_write(ioaddr, phy_id, MII_CTRL1000, ADVERTISE_1000FULL);


	mdio_write(ioaddr, phy_id, MII_BMCR,
		   BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET);
}
