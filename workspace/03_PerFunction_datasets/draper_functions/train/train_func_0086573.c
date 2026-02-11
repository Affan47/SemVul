ar9300_eeprom_restore_flash(struct ath_hw *ah, u8 *mptr,
				       int mdata_size)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u16 *data = (u16 *) mptr;
	int i;

	for (i = 0; i < mdata_size / 2; i++, data++)
		ath9k_hw_nvram_read(common, i, data);

	return 0;
}
