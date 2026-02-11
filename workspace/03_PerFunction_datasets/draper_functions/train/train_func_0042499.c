lpphy_rev2plus_set_rx_gain(struct b43_wldev *dev, u32 gain)
{
	u16 low_gain = gain & 0xFFFF;
	u16 high_gain = (gain >> 16) & 0xF;
	u16 ext_lna = (gain >> 21) & 0x1;
	u16 trsw = ~(gain >> 20) & 0x1;
	u16 tmp;

	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_VAL_0, 0xFFFE, trsw);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
			0xFDFF, ext_lna << 9);
	b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
			0xFBFF, ext_lna << 10);
	b43_phy_write(dev, B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL, low_gain);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFFF0, high_gain);
	if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
		tmp = (gain >> 2) & 0x3;
		b43_phy_maskset(dev, B43_LPPHY_RF_OVERRIDE_2_VAL,
				0xE7FF, tmp<<11);
		b43_phy_maskset(dev, B43_PHY_OFDM(0xE6), 0xFFE7, tmp << 3);
	}
}
