tulip_mdio_read(struct net_device *dev, int phy_id, int location)
{
	struct tulip_private *tp = netdev_priv(dev);
	int i;
	int read_cmd = (0xf6 << 10) | ((phy_id & 0x1f) << 5) | location;
	int retval = 0;
	void __iomem *ioaddr = tp->base_addr;
	void __iomem *mdio_addr = ioaddr + CSR9;
	unsigned long flags;

	if (location & ~0x1f)
		return 0xffff;

	if (tp->chip_id == COMET  &&  phy_id == 30) {
		if (comet_miireg2offset[location])
			return ioread32(ioaddr + comet_miireg2offset[location]);
		return 0xffff;
	}

	spin_lock_irqsave(&tp->mii_lock, flags);
	if (tp->chip_id == LC82C168) {
		iowrite32(0x60020000 + (phy_id<<23) + (location<<18), ioaddr + 0xA0);
		ioread32(ioaddr + 0xA0);
		ioread32(ioaddr + 0xA0);
		for (i = 1000; i >= 0; --i) {
			barrier();
			if ( ! ((retval = ioread32(ioaddr + 0xA0)) & 0x80000000))
				break;
		}
		spin_unlock_irqrestore(&tp->mii_lock, flags);
		return retval & 0xffff;
	}


	for (i = 32; i >= 0; i--) {
		iowrite32(MDIO_ENB | MDIO_DATA_WRITE1, mdio_addr);
		mdio_delay();
		iowrite32(MDIO_ENB | MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	}

	for (i = 15; i >= 0; i--) {
		int dataval = (read_cmd & (1 << i)) ? MDIO_DATA_WRITE1 : 0;

		iowrite32(MDIO_ENB | dataval, mdio_addr);
		mdio_delay();
		iowrite32(MDIO_ENB | dataval | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	}

	for (i = 19; i > 0; i--) {
		iowrite32(MDIO_ENB_IN, mdio_addr);
		mdio_delay();
		retval = (retval << 1) | ((ioread32(mdio_addr) & MDIO_DATA_READ) ? 1 : 0);
		iowrite32(MDIO_ENB_IN | MDIO_SHIFT_CLK, mdio_addr);
		mdio_delay();
	}

	spin_unlock_irqrestore(&tp->mii_lock, flags);
	return (retval>>1) & 0xffff;
}
