mdio_read(void __iomem *ioaddr, int phy_id, int location)
{
	int i;

	iowrite16((phy_id<<8) + location, ioaddr + MII_Addr);
	iowrite16(1, ioaddr + MII_Cmd);
	for (i = 10000; i >= 0; i--)
		if ((ioread16(ioaddr + MII_Status) & 1) == 0)
			break;
	return ioread16(ioaddr + MII_Rd_Data);
}
