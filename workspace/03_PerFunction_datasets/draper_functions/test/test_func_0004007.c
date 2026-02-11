vsc824x_add_skew(struct phy_device *phydev)
{
	int err;
	int extcon;

	extcon = phy_read(phydev, MII_VSC8244_EXT_CON1);

	if (extcon < 0)
		return extcon;

	extcon &= ~(MII_VSC8244_EXTCON1_TX_SKEW_MASK |
			MII_VSC8244_EXTCON1_RX_SKEW_MASK);

	extcon |= (MII_VSC8244_EXTCON1_TX_SKEW |
			MII_VSC8244_EXTCON1_RX_SKEW);

	err = phy_write(phydev, MII_VSC8244_EXT_CON1, extcon);

	return err;
}
