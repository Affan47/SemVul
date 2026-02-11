bcm5461_read_link(struct mii_phy* phy)
{
	u32 phy_reg;
	int mode;


	sungem_phy_write(phy, MII_NCONFIG, 0x7c00);
	phy_reg = sungem_phy_read(phy, MII_NCONFIG);

	mode = (phy_reg & BCM5461_MODE_MASK ) >> 1;

	if ( mode == BCM54XX_COPPER) {
		return bcm54xx_read_link(phy);
	}

	phy->speed = SPEED_1000;


	sungem_phy_write(phy, MII_NCONFIG, 0x7000);
	phy_reg = sungem_phy_read(phy, MII_NCONFIG);

	if (phy_reg & BCM5461_FIBER_DUPLEX)
		phy->duplex |=  DUPLEX_FULL;
	else
		phy->duplex |=  DUPLEX_HALF;

	return 0;
}
