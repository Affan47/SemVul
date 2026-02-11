mv88e1xxx_set_speed_duplex(struct cphy *phy, int speed, int duplex)
{
	u32 ctl;

	(void) simple_mdio_read(phy, MII_BMCR, &ctl);
	if (speed >= 0) {
		ctl &= ~(BMCR_SPEED100 | BMCR_SPEED1000 | BMCR_ANENABLE);
		if (speed == SPEED_100)
			ctl |= BMCR_SPEED100;
		else if (speed == SPEED_1000)
			ctl |= BMCR_SPEED1000;
	}
	if (duplex >= 0) {
		ctl &= ~(BMCR_FULLDPLX | BMCR_ANENABLE);
		if (duplex == DUPLEX_FULL)
			ctl |= BMCR_FULLDPLX;
	}
	if (ctl & BMCR_SPEED1000)
		ctl |= BMCR_ANENABLE;
	(void) simple_mdio_write(phy, MII_BMCR, ctl);
	return 0;
}
