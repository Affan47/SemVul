b43_phy_maskset(struct b43_wldev *dev, u16 offset, u16 mask, u16 set)
{
	if (dev->phy.ops->phy_maskset) {
		assert_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, mask, set);
	} else {
		b43_phy_write(dev, offset,
			      (b43_phy_read(dev, offset) & mask) | set);
	}
}
