b43legacy_phy_lo_g_deviation_subval(struct b43legacy_wldev *dev,
					u16 control)
{
	struct b43legacy_phy *phy = &dev->phy;
	u16 ret;
	unsigned long flags;

	local_irq_save(flags);
	if (phy->gmode) {
		b43legacy_phy_write(dev, 0x15, 0xE300);
		control <<= 8;
		b43legacy_phy_write(dev, 0x0812, control | 0x00B0);
		udelay(5);
		b43legacy_phy_write(dev, 0x0812, control | 0x00B2);
		udelay(2);
		b43legacy_phy_write(dev, 0x0812, control | 0x00B3);
		udelay(4);
		b43legacy_phy_write(dev, 0x0015, 0xF300);
		udelay(8);
	} else {
		b43legacy_phy_write(dev, 0x0015, control | 0xEFA0);
		udelay(2);
		b43legacy_phy_write(dev, 0x0015, control | 0xEFE0);
		udelay(4);
		b43legacy_phy_write(dev, 0x0015, control | 0xFFE0);
		udelay(8);
	}
	ret = b43legacy_phy_read(dev, 0x002D);
	local_irq_restore(flags);
	b43legacy_voluntary_preempt();

	return ret;
}
