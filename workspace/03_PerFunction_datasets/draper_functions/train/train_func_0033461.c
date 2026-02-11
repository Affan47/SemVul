mii_nway_restart (struct mii_if_info *mii)
{
	int bmcr;
	int r = -EINVAL;


	bmcr = mii->mdio_read(mii->dev, mii->phy_id, MII_BMCR);

	if (bmcr & BMCR_ANENABLE) {
		bmcr |= BMCR_ANRESTART;
		mii->mdio_write(mii->dev, mii->phy_id, MII_BMCR, bmcr);
		r = 0;
	}

	return r;
}
