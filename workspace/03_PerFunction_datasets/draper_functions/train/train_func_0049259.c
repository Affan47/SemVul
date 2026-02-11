mdio_sync(unsigned int ioaddr, int bits)
{
	unsigned int mdio_addr = ioaddr + Wn4_PhysicalMgmt;


	while (-- bits >= 0) {
		outw(MDIO_DATA_WRITE1, mdio_addr);
		outw(MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
	}
}
