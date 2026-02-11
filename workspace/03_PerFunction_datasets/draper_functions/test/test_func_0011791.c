ath5k_hw_radio_revision(struct ath5k_hw *ah, enum ieee80211_band band)
{
	unsigned int i;
	u32 srev;
	u16 ret;


	switch (band) {
	case IEEE80211_BAND_2GHZ:
		ath5k_hw_reg_write(ah, AR5K_PHY_SHIFT_2GHZ, AR5K_PHY(0));
		break;
	case IEEE80211_BAND_5GHZ:
		ath5k_hw_reg_write(ah, AR5K_PHY_SHIFT_5GHZ, AR5K_PHY(0));
		break;
	default:
		return 0;
	}

	usleep_range(2000, 2500);


	ath5k_hw_reg_write(ah, 0x00001c16, AR5K_PHY(0x34));

	for (i = 0; i < 8; i++)
		ath5k_hw_reg_write(ah, 0x00010000, AR5K_PHY(0x20));

	if (ah->ah_version == AR5K_AR5210) {
		srev = (ath5k_hw_reg_read(ah, AR5K_PHY(256)) >> 28) & 0xf;
		ret = (u16)ath5k_hw_bitswap(srev, 4) + 1;
	} else {
		srev = (ath5k_hw_reg_read(ah, AR5K_PHY(0x100)) >> 24) & 0xff;
		ret = (u16)ath5k_hw_bitswap(((srev & 0xf0) >> 4) |
				((srev & 0x0f) << 4), 8);
	}


	ath5k_hw_reg_write(ah, AR5K_PHY_SHIFT_5GHZ, AR5K_PHY(0));

	return ret;
}
