__ath9k_hw_ar9287_fill_eeprom(struct ath_hw *ah)
{
	struct ar9287_eeprom *eep = &ah->eeprom.map9287;
	u16 *eep_data;
	int addr, eep_start_loc = AR9287_EEP_START_LOC;
	eep_data = (u16 *)eep;

	for (addr = 0; addr < SIZE_EEPROM_AR9287; addr++) {
		if (!ath9k_hw_nvram_read(ah, addr + eep_start_loc, eep_data))
			return false;
		eep_data++;
	}

	return true;
}
