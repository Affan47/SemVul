ar9003_paprd_set_txpower(struct ath_hw *ah,
				     struct ath9k_channel *chan,
				     u8 *targetPowerValT2)
{
	int i;

	if (!ar9003_is_paprd_enabled(ah))
		return;

	if (IS_CHAN_HT40(chan))
		i = ALL_TARGET_HT40_7;
	else
		i = ALL_TARGET_HT20_7;

	if (IS_CHAN_2GHZ(chan)) {
		if (!AR_SREV_9330(ah) && !AR_SREV_9340(ah) &&
		    !AR_SREV_9462(ah) && !AR_SREV_9565(ah)) {
			if (IS_CHAN_HT40(chan))
				i = ALL_TARGET_HT40_0_8_16;
			else
				i = ALL_TARGET_HT20_0_8_16;
		}
	}

	ah->paprd_target_power = targetPowerValT2[i];
}
