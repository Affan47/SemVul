b43legacy_rate_memory_init(struct b43legacy_wldev *dev)
{
	switch (dev->phy.type) {
	case B43legacy_PHYTYPE_G:
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_6MB, 1);
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_12MB, 1);
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_18MB, 1);
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_24MB, 1);
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_36MB, 1);
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_48MB, 1);
		b43legacy_rate_memory_write(dev, B43legacy_OFDM_RATE_54MB, 1);

	case B43legacy_PHYTYPE_B:
		b43legacy_rate_memory_write(dev, B43legacy_CCK_RATE_1MB, 0);
		b43legacy_rate_memory_write(dev, B43legacy_CCK_RATE_2MB, 0);
		b43legacy_rate_memory_write(dev, B43legacy_CCK_RATE_5MB, 0);
		b43legacy_rate_memory_write(dev, B43legacy_CCK_RATE_11MB, 0);
		break;
	default:
		B43legacy_BUG_ON(1);
	}
}
