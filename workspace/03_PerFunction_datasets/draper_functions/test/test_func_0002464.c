xcvr_init_1g_rgmii(struct niu *np)
{
	int err;
	u64 val;
	u16 bmcr, bmsr, estat;

	val = nr64(MIF_CONFIG);
	val &= ~MIF_CONFIG_INDIRECT_MODE;
	nw64(MIF_CONFIG, val);

	err = mii_reset(np);
	if (err)
		return err;

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		return err;
	bmsr = err;

	estat = 0;
	if (bmsr & BMSR_ESTATEN) {
		err = mii_read(np, np->phy_addr, MII_ESTATUS);
		if (err < 0)
			return err;
		estat = err;
	}

	bmcr = 0;
	err = mii_write(np, np->phy_addr, MII_BMCR, bmcr);
	if (err)
		return err;

	if (bmsr & BMSR_ESTATEN) {
		u16 ctrl1000 = 0;

		if (estat & ESTATUS_1000_TFULL)
			ctrl1000 |= ADVERTISE_1000FULL;
		err = mii_write(np, np->phy_addr, MII_CTRL1000, ctrl1000);
		if (err)
			return err;
	}

	bmcr = (BMCR_SPEED1000 | BMCR_FULLDPLX);

	err = mii_write(np, np->phy_addr, MII_BMCR, bmcr);
	if (err)
		return err;

	err = mii_read(np, np->phy_addr, MII_BMCR);
	if (err < 0)
		return err;
	bmcr = mii_read(np, np->phy_addr, MII_BMCR);

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		return err;

	return 0;
}
