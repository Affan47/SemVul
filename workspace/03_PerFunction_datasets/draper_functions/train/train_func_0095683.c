mdio_write(struct nic *nic __unused, int phy_id, int location, int value)
{
    int i;
    int cmd = (0x5002 << 16) | (phy_id << 23) | (location<<18) | value;
    long mdio_addr = ioaddr + CSR9;

#ifdef TULIP_DEBUG_WHERE
    whereami("mdio_write\n");
#endif

    if (tp->chip_id == LC82C168) {
	int i = 1000;
	outl(cmd, ioaddr + 0xA0);
	do
	    if ( ! (inl(ioaddr + 0xA0) & 0x80000000))
		break;
	while (--i > 0);
	return;
    }

    if (tp->chip_id == COMET) {
	if (phy_id != 1)
	    return;
	if (location < 7)
	    outl(value, ioaddr + 0xB4 + (location<<2));
	else if (location == 17)
	    outl(value, ioaddr + 0xD0);
	else if (location >= 29 && location <= 31)
	    outl(value, ioaddr + 0xD4 + ((location-29)<<2));
	return;
    }


    for (i = 32; i >= 0; i--) {
	outl(MDIO_ENB | MDIO_DATA_WRITE1, mdio_addr);
	mdio_delay();
	outl(MDIO_ENB | MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
	mdio_delay();
    }

    for (i = 31; i >= 0; i--) {
	int dataval = (cmd & (1 << i)) ? MDIO_DATA_WRITE1 : 0;
	outl(MDIO_ENB | dataval, mdio_addr);
	mdio_delay();
	outl(MDIO_ENB | dataval | MDIO_SHIFT_CLK, mdio_addr);
	mdio_delay();
    }

    for (i = 2; i > 0; i--) {
	outl(MDIO_ENB_IN, mdio_addr);
	mdio_delay();
	outl(MDIO_ENB_IN | MDIO_SHIFT_CLK, mdio_addr);
	mdio_delay();
    }
}
