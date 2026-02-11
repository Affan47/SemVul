bcm5482_read_status(struct phy_device *phydev)
{
	int err;

	err = genphy_read_status(phydev);

	if (phydev->dev_flags & PHY_BCM_FLAGS_MODE_1000BX) {


		if (phydev->link) {
			phydev->speed = SPEED_1000;
			phydev->duplex = DUPLEX_FULL;
		}
	}

	return err;
}
