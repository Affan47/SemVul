b43_phy_ht_pa_override(struct b43_wldev *dev, bool enable)
{
	struct b43_phy_ht *htphy = dev->phy.ht;
	static const u16 regs[3] = { B43_PHY_HT_RF_CTL_INT_C1,
				     B43_PHY_HT_RF_CTL_INT_C2,
				     B43_PHY_HT_RF_CTL_INT_C3 };
	int i;

	if (enable) {
		for (i = 0; i < 3; i++)
			b43_phy_write(dev, regs[i], htphy->rf_ctl_int_save[i]);
	} else {
		for (i = 0; i < 3; i++)
			htphy->rf_ctl_int_save[i] = b43_phy_read(dev, regs[i]);

		for (i = 0; i < 3; i++)
			b43_phy_write(dev, regs[i], 0x0400);
	}
}
