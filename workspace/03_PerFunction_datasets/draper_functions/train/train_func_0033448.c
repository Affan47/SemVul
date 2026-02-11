rtl8187se_write_ofdm_config(struct ieee80211_hw *dev)
{

	int i;

	for (i = 0; i < 60; i++)
		rtl8225se_write_phy_ofdm(dev, i, OFDM_CONFIG[i]);

}
