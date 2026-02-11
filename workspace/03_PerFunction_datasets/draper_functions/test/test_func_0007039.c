rhine_check_media(struct net_device *dev, unsigned int init_media)
{
	struct rhine_private *rp = netdev_priv(dev);
	void __iomem *ioaddr = rp->base;

	if (!rp->mii_if.force_media)
		mii_check_media(&rp->mii_if, netif_msg_link(rp), init_media);

	if (rp->mii_if.full_duplex)
	    iowrite8(ioread8(ioaddr + ChipCmd1) | Cmd1FDuplex,
		   ioaddr + ChipCmd1);
	else
	    iowrite8(ioread8(ioaddr + ChipCmd1) & ~Cmd1FDuplex,
		   ioaddr + ChipCmd1);

	netif_info(rp, link, dev, "force_media %d, carrier %d\n",
		   rp->mii_if.force_media, netif_carrier_ok(dev));
}
