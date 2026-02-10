ael2005_get_module_type(struct cphy *phy, int delay_ms)
{
	int v;
	unsigned int stat;

	v = t3_mdio_read(phy, MDIO_MMD_PMAPMD, AEL2005_GPIO_CTRL, &stat);
	if (v)
		return v;

	if (stat & (1 << 8))
		return phy_modtype_none;

	return ael2xxx_get_module_type(phy, delay_ms);
}
