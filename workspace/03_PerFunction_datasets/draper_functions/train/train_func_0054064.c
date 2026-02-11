netdev_error(struct net_device *dev, int intr_status)
{
	struct netdev_private *np = netdev_priv(dev);
	void __iomem *ioaddr = np->base;
	u16 mii_ctl, mii_advertise, mii_lpa;
	int speed;

	if (intr_status & LinkChange) {
		if (mdio_wait_link(dev, 10) == 0) {
			printk(KERN_INFO "%s: Link up\n", dev->name);
			if (np->an_enable) {
				mii_advertise = mdio_read(dev, np->phys[0],
							   MII_ADVERTISE);
				mii_lpa = mdio_read(dev, np->phys[0], MII_LPA);
				mii_advertise &= mii_lpa;
				printk(KERN_INFO "%s: Link changed: ",
					dev->name);
				if (mii_advertise & ADVERTISE_100FULL) {
					np->speed = 100;
					printk("100Mbps, full duplex\n");
				} else if (mii_advertise & ADVERTISE_100HALF) {
					np->speed = 100;
					printk("100Mbps, half duplex\n");
				} else if (mii_advertise & ADVERTISE_10FULL) {
					np->speed = 10;
					printk("10Mbps, full duplex\n");
				} else if (mii_advertise & ADVERTISE_10HALF) {
					np->speed = 10;
					printk("10Mbps, half duplex\n");
				} else
					printk("\n");

			} else {
				mii_ctl = mdio_read(dev, np->phys[0], MII_BMCR);
				speed = (mii_ctl & BMCR_SPEED100) ? 100 : 10;
				np->speed = speed;
				printk(KERN_INFO "%s: Link changed: %dMbps ,",
					dev->name, speed);
				printk("%s duplex.\n",
					(mii_ctl & BMCR_FULLDPLX) ?
						"full" : "half");
			}
			check_duplex(dev);
			if (np->flowctrl && np->mii_if.full_duplex) {
				iowrite16(ioread16(ioaddr + MulticastFilter1+2) | 0x0200,
					ioaddr + MulticastFilter1+2);
				iowrite16(ioread16(ioaddr + MACCtrl0) | EnbFlowCtrl,
					ioaddr + MACCtrl0);
			}
			netif_carrier_on(dev);
		} else {
			printk(KERN_INFO "%s: Link down\n", dev->name);
			netif_carrier_off(dev);
		}
	}
	if (intr_status & StatsMax) {
		get_stats(dev);
	}
	if (intr_status & IntrPCIErr) {
		printk(KERN_ERR "%s: Something Wicked happened! %4.4x.\n",
			   dev->name, intr_status);

	}
}
