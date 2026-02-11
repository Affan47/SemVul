r2059_upload_inittabs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u16 *table = NULL;
	u16 size, i;

	switch (phy->rev) {
	case 1:
		table = r2059_phy_rev1_init[0];
		size = ARRAY_SIZE(r2059_phy_rev1_init);
		break;
	default:
		B43_WARN_ON(1);
		return;
	}

	for (i = 0; i < size; i++, table += 2)
		b43_radio_write(dev, R2059_ALL | table[0], table[1]);
}
