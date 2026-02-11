ar9003_hw_xpa_bias_level_get(struct ath_hw *ah, int is2ghz)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	if (is2ghz)
		return eep->modalHeader2G.xpaBiasLvl;
	else
		return eep->modalHeader5G.xpaBiasLvl;
}
