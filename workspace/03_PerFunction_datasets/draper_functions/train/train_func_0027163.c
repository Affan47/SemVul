b43legacy_phy_init(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	int err = -ENODEV;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
		switch (phy->rev) {
		case 2:
			b43legacy_phy_initb2(dev);
			err = 0;
			break;
		case 4:
			b43legacy_phy_initb4(dev);
			err = 0;
			break;
		case 5:
			b43legacy_phy_initb5(dev);
			err = 0;
			break;
		case 6:
			b43legacy_phy_initb6(dev);
			err = 0;
			break;
		}
		break;
	case B43legacy_PHYTYPE_G:
		b43legacy_phy_initg(dev);
		err = 0;
		break;
	}
	if (err)
		b43legacyerr(dev->wl, "Unknown PHYTYPE found\n");

	return err;
}
