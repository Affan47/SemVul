b43_nphy_get_inittabs_rev3(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	switch (dev->phy.rev) {
	case 3:
		return &b2056_inittab_phy_rev3;
	case 4:
		return &b2056_inittab_phy_rev4;
	default:
		switch (phy->radio_rev) {
		case 5:
			return &b2056_inittab_radio_rev5;
		case 6:
			return &b2056_inittab_radio_rev6;
		case 7:
		case 9:
			return &b2056_inittab_radio_rev7_9;
		case 8:
			return &b2056_inittab_radio_rev8;
		case 11:
			return &b2056_inittab_radio_rev11;
		}
	}

	return NULL;
}
