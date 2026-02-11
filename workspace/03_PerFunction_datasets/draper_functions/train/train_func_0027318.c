ath5k_set_beacon_filter(struct ieee80211_hw *hw, bool enable)
{
	struct ath5k_hw *ah = hw->priv;
	u32 rfilt;
	rfilt = ath5k_hw_get_rx_filter(ah);
	if (enable)
		rfilt |= AR5K_RX_FILTER_BEACON;
	else
		rfilt &= ~AR5K_RX_FILTER_BEACON;
	ath5k_hw_set_rx_filter(ah, rfilt);
	ah->filter_flags = rfilt;
}
