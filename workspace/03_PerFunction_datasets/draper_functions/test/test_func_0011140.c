ath9k_hw_chip_reset(struct ath_hw *ah,
				struct ath9k_channel *chan)
{
	if (AR_SREV_9280(ah) && ah->eep_ops->get_eeprom(ah, EEP_OL_PWRCTRL)) {
		if (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_POWER_ON))
			return 0;
	} else if (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_WARM))
		return 0;

	if (!ath9k_hw_setpower(ah, ATH9K_PM_AWAKE))
		return 0;

	ah->chip_fullsleep = 0;
	ath9k_hw_init_pll(ah, chan);
	ath9k_hw_set_rfmode(ah, chan);

	return 1;
}
