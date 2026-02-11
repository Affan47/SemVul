ath5k_eeprom_init(struct ath5k_hw *ah)
{
	int err;

	err = ath5k_eeprom_init_header(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_init_modes(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_read_pcal_info(ah);
	if (err < 0)
		return err;

	err = ath5k_eeprom_read_ctl_info(ah);
	if (err < 0)
		return err;

	return 0;
}
