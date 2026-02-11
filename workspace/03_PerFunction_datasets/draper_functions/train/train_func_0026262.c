mdio_read(struct nic *nic __unused, int phy_id, unsigned int location)
{
	long mdio_addr = BASE + MIICtrl;
	int mii_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	int i, retval = 0;

	if (sdc->mii_preamble_required)
		mdio_sync(mdio_addr);


	for (i = 15; i >= 0; i--) {
		int dataval =
		    (mii_cmd & (1 << i)) ? MDIO_WRITE1 : MDIO_WRITE0;

		mdio_out(dataval, mdio_addr);
		mdio_delay(mdio_addr);
		mdio_out(dataval | MDIO_ShiftClk, mdio_addr);
		mdio_delay(mdio_addr);
	}

	for (i = 19; i > 0; i--) {
		mdio_out(MDIO_EnbIn, mdio_addr);
		mdio_delay(mdio_addr);
		retval = (retval << 1) | ((mdio_in(mdio_addr) & MDIO_Data)
					  ? 1 : 0);
		mdio_out(MDIO_EnbIn | MDIO_ShiftClk, mdio_addr);
		mdio_delay(mdio_addr);
	}
	return (retval >> 1) & 0xffff;
}
