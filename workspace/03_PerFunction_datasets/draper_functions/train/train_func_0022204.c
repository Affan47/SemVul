phy_sanitize_settings(struct phy_device *phydev)
{
	u32 features = phydev->supported;
	unsigned int idx;


	if ((features & SUPPORTED_Autoneg) == 0)
		phydev->autoneg = AUTONEG_DISABLE;

	idx = phy_find_valid(phy_find_setting(phydev->speed, phydev->duplex),
			features);

	phydev->speed = settings[idx].speed;
	phydev->duplex = settings[idx].duplex;
}
