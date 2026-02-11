et1011c_config_aneg(struct phy_device *phydev)
{
	int ctl = 0;
	ctl = phy_read(phydev, MII_BMCR);
	if (ctl < 0)
		return ctl;
	ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 | BMCR_SPEED1000 |
		 BMCR_ANENABLE);

	phy_write(phydev, MII_BMCR, ctl | BMCR_RESET);

	return genphy_config_aneg(phydev);
}
