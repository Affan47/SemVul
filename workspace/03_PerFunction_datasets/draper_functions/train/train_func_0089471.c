b43_radio_lock(struct b43_wldev *dev)
{
	u32 macctl;

#if B43_DEBUG
	B43_WARN_ON(dev->phy.radio_locked);
	dev->phy.radio_locked = true;
#endif

	macctl = b43_read32(dev, B43_MMIO_MACCTL);
	macctl |= B43_MACCTL_RADIOLOCK;
	b43_write32(dev, B43_MMIO_MACCTL, macctl);


	b43_read32(dev, B43_MMIO_MACCTL);
	udelay(10);
}
