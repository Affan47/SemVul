mdio_sync(void __iomem *mdio_addr)
{
	int bits = 32;


	while (--bits >= 0) {
		iowrite8(MDIO_WRITE1, mdio_addr);
		mdio_delay();
		iowrite8(MDIO_WRITE1 | MDIO_ShiftClk, mdio_addr);
		mdio_delay();
	}
}
