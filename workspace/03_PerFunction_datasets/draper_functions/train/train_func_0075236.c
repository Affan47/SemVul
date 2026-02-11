b43legacy_phy_unlock(struct b43legacy_wldev *dev)
{
#if B43legacy_DEBUG
	B43legacy_WARN_ON(!dev->phy.phy_locked);
	dev->phy.phy_locked = 0;
#endif

	if (dev->dev->id.revision < 3) {
		b43legacy_mac_enable(dev);
	} else {
		if (!b43legacy_is_mode(dev->wl, NL80211_IFTYPE_AP))
			b43legacy_power_saving_ctl_bits(dev, -1, -1);
	}
}
