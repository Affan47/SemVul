netdev_get_sopass(struct net_device *dev, u8 *data)
{
	struct netdev_private *np = netdev_priv(dev);
	void __iomem * ioaddr = ns_ioaddr(dev);
	u16 *sval = (u16 *)data;
	u32 addr;

	if (np->srr < SRR_DP83815_D) {
		sval[0] = sval[1] = sval[2] = 0;
		return 0;
	}


	addr = readl(ioaddr + RxFilterAddr) & ~RFCRAddressMask;

	writel(addr | 0xa, ioaddr + RxFilterAddr);
	sval[0] = readw(ioaddr + RxFilterData);

	writel(addr | 0xc, ioaddr + RxFilterAddr);
	sval[1] = readw(ioaddr + RxFilterData);

	writel(addr | 0xe, ioaddr + RxFilterAddr);
	sval[2] = readw(ioaddr + RxFilterData);

	writel(addr, ioaddr + RxFilterAddr);

	return 0;
}
