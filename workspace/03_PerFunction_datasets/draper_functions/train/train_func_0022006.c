b43_ofdmtab_read16(struct b43_wldev *dev, u16 table, u16 offset)
{
	struct b43_phy_g *gphy = dev->phy.g;
	u16 addr;

	addr = table + offset;
	if ((gphy->ofdmtab_addr_direction != B43_OFDMTAB_DIRECTION_READ) ||
	    (addr - 1 != gphy->ofdmtab_addr)) {

		b43_phy_write(dev, B43_PHY_OTABLECTL, addr);
		gphy->ofdmtab_addr_direction = B43_OFDMTAB_DIRECTION_READ;
	}
	gphy->ofdmtab_addr = addr;

	return b43_phy_read(dev, B43_PHY_OTABLEI);


	assert_sizes();
}
