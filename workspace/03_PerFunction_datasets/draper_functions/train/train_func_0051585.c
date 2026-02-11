rhine_power_init(struct net_device *dev)
{
	struct rhine_private *rp = netdev_priv(dev);
	void __iomem *ioaddr = rp->base;
	u16 wolstat;

	if (rp->quirks & rqWOL) {

		iowrite8(ioread8(ioaddr + StickyHW) & 0xFC, ioaddr + StickyHW);


		iowrite8(0x80, ioaddr + WOLcgClr);


		iowrite8(0xFF, ioaddr + WOLcrClr);

		if (rp->quirks & rq6patterns)
			iowrite8(0x03, ioaddr + WOLcrClr1);


		wolstat = ioread8(ioaddr + PwrcsrSet);
		if (rp->quirks & rq6patterns)
			wolstat |= (ioread8(ioaddr + PwrcsrSet1) & 0x03) << 8;


		iowrite8(0xFF, ioaddr + PwrcsrClr);
		if (rp->quirks & rq6patterns)
			iowrite8(0x03, ioaddr + PwrcsrClr1);

		if (wolstat) {
			char *reason;
			switch (wolstat) {
			case WOLmagic:
				reason = "Magic packet";
				break;
			case WOLlnkon:
				reason = "Link went up";
				break;
			case WOLlnkoff:
				reason = "Link went down";
				break;
			case WOLucast:
				reason = "Unicast packet";
				break;
			case WOLbmcast:
				reason = "Multicast/broadcast packet";
				break;
			default:
				reason = "Unknown";
			}
			netdev_info(dev, "Woke system up. Reason: %s\n",
				    reason);
		}
	}
}
