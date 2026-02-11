sis900_init_rxfilter (struct net_device * net_dev)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	void __iomem *ioaddr = sis_priv->ioaddr;
	u32 rfcrSave;
	u32 i;

	rfcrSave = sr32(rfcr);


	sw32(rfcr, rfcrSave & ~RFEN);


	for (i = 0 ; i < 3 ; i++) {
		u32 w = (u32) *((u16 *)(net_dev->dev_addr)+i);

		sw32(rfcr, i << RFADDR_shift);
		sw32(rfdr, w);

		if (netif_msg_hw(sis_priv)) {
			printk(KERN_DEBUG "%s: Receive Filter Addrss[%d]=%x\n",
			       net_dev->name, i, sr32(rfdr));
		}
	}


	sw32(rfcr, rfcrSave | RFEN);
}
