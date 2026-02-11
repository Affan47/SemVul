b43legacy_radio_clear_tssi(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
	case B43legacy_PHYTYPE_G:
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0058,
				      0x7F7F);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x005a,
				      0x7F7F);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0070,
				      0x7F7F);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0072,
				      0x7F7F);
		break;
	}
}
