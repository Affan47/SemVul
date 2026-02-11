check_media(struct net_device *dev)
{
	struct epic_private *ep = netdev_priv(dev);
	void __iomem *ioaddr = ep->ioaddr;
	int mii_lpa = ep->mii_phy_cnt ? mdio_read(dev, ep->phys[0], MII_LPA) : 0;
	int negotiated = mii_lpa & ep->mii.advertising;
	int duplex = (negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040;

	if (ep->mii.force_media)
		return;
	if (mii_lpa == 0xffff)
		return;
	if (ep->mii.full_duplex != duplex) {
		ep->mii.full_duplex = duplex;
		netdev_info(dev, "Setting %s-duplex based on MII #%d link partner capability of %4.4x.\n",
			    ep->mii.full_duplex ? "full" : "half",
			    ep->phys[0], mii_lpa);
		ew32(TxCtrl, ep->mii.full_duplex ? 0x7F : 0x79);
	}
}
