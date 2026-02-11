ath5k_hw_get_default_slottime(struct ath5k_hw *ah)
{
	struct ieee80211_channel *channel = ah->ah_current_channel;
	unsigned int slot_time;

	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_40MHZ:
		slot_time = AR5K_INIT_SLOT_TIME_TURBO;
		break;
	case AR5K_BWMODE_10MHZ:
		slot_time = AR5K_INIT_SLOT_TIME_HALF_RATE;
		break;
	case AR5K_BWMODE_5MHZ:
		slot_time = AR5K_INIT_SLOT_TIME_QUARTER_RATE;
		break;
	case AR5K_BWMODE_DEFAULT:
	default:
		slot_time = AR5K_INIT_SLOT_TIME_DEFAULT;
		if ((channel->hw_value == AR5K_MODE_11B) && !ah->ah_short_slot)
			slot_time = AR5K_INIT_SLOT_TIME_B;
		break;
	}

	return slot_time;
}
