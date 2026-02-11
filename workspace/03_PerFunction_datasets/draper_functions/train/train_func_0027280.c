__ath9k_hw_ar9287_fill_eeprom(struct ath_hw *ah)
{
	struct ar9287_eeprom *eep = &ah->eeprom.map9287;
	struct ath_common *common = ath9k_hw_common(ah);
	u16 *eep_data;
	unsigned int addr;
	int eep_start_loc = AR9287_EEP_START_LOC;
	eep_data = (u16 *)eep;

	for (addr = 0; addr < SIZE_EEPROM_AR9287; addr++) {
		if (!ath9k_hw_nvram_read(common, addr + eep_start_loc,
					 eep_data)) {
			DBG("ath9k: "
				"Unable to read eeprom region\n");
			return 0;
		}
		eep_data++;
	}

	return 1;
}
