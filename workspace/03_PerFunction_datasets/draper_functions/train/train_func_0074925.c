b43legacy_radio_read16(struct b43legacy_wldev *dev, u16 offset)
{
	struct b43legacy_phy *phy = &dev->phy;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
		if (phy->radio_ver == 0x2053) {
			if (offset < 0x70)
				offset += 0x80;
			else if (offset < 0x80)
				offset += 0x70;
		} else if (phy->radio_ver == 0x2050)
			offset |= 0x80;
		else
			B43legacy_WARN_ON(1);
		break;
	case B43legacy_PHYTYPE_G:
		offset |= 0x80;
		break;
	default:
		B43legacy_BUG_ON(1);
	}

	b43legacy_write16(dev, B43legacy_MMIO_RADIO_CONTROL, offset);
	return b43legacy_read16(dev, B43legacy_MMIO_RADIO_DATA_LOW);
}
