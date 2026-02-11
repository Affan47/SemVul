ath9k_hw_deinit(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	if (common->state < ATH_HW_INITIALIZED)
		goto free_hw;

	ath9k_hw_setpower(ah, ATH9K_PM_FULL_SLEEP);

free_hw:
	ath9k_hw_rf_free_ext_banks(ah);
}
