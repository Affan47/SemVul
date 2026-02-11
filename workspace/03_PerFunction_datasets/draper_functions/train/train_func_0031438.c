lpphy_set_rx_gain(struct b43_wldev *dev, u32 gain)
{
	if (dev->phy.rev < 2)
		lpphy_rev0_1_set_rx_gain(dev, gain);
	else
		lpphy_rev2plus_set_rx_gain(dev, gain);
	lpphy_enable_rx_gain_override(dev);
}
