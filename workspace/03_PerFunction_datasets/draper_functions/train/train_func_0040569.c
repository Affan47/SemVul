ath5k_eeprom_read_turbo_modes(struct ath5k_hw *ah,
			      u32 *offset, unsigned int mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 o = *offset;
	u16 val;
	int ret;

	if (ee->ee_version < AR5K_EEPROM_VERSION_5_0)
		return 0;

	switch (mode){
	case AR5K_EEPROM_MODE_11A:
		ee->ee_switch_settling_turbo[mode] = (val >> 6) & 0x7f;

		ee->ee_atn_tx_rx_turbo[mode] = (val >> 13) & 0x7;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_atn_tx_rx_turbo[mode] |= (val & 0x7) << 3;
		ee->ee_margin_tx_rx_turbo[mode] = (val >> 3) & 0x3f;

		ee->ee_adc_desired_size_turbo[mode] = (val >> 9) & 0x7f;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_adc_desired_size_turbo[mode] |= (val & 0x1) << 7;
		ee->ee_pga_desired_size_turbo[mode] = (val >> 1) & 0xff;

		if (AR5K_EEPROM_EEMAP(ee->ee_misc0) >=2)
			ee->ee_pd_gain_overlap = (val >> 9) & 0xf;
		break;
	case AR5K_EEPROM_MODE_11G:
		ee->ee_switch_settling_turbo[mode] = (val >> 8) & 0x7f;

		ee->ee_atn_tx_rx_turbo[mode] = (val >> 15) & 0x7;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_atn_tx_rx_turbo[mode] |= (val & 0x1f) << 1;
		ee->ee_margin_tx_rx_turbo[mode] = (val >> 5) & 0x3f;

		ee->ee_adc_desired_size_turbo[mode] = (val >> 11) & 0x7f;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_adc_desired_size_turbo[mode] |= (val & 0x7) << 5;
		ee->ee_pga_desired_size_turbo[mode] = (val >> 3) & 0xff;
		break;
	}


	*offset = o;

	return 0;
}
