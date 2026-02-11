lpphy_baseband_init(struct b43_wldev *dev)
{
	lpphy_table_init(dev);
	if (dev->phy.rev >= 2)
		lpphy_baseband_rev2plus_init(dev);
	else
		lpphy_baseband_rev0_1_init(dev);
}
