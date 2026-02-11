rt61pci_config_lna_gain(struct rt2x00_dev *rt2x00dev,
				    struct rt2x00lib_conf *libconf)
{
	u16 eeprom;
	short lna_gain = 0;

	if (libconf->conf->chandef.chan->band == IEEE80211_BAND_2GHZ) {
		if (rt2x00_has_cap_external_lna_bg(rt2x00dev))
			lna_gain += 14;

		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_OFFSET_BG, &eeprom);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_BG_1);
	} else {
		if (rt2x00_has_cap_external_lna_a(rt2x00dev))
			lna_gain += 14;

		rt2x00_eeprom_read(rt2x00dev, EEPROM_RSSI_OFFSET_A, &eeprom);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_A_1);
	}

	rt2x00dev->lna_gain = lna_gain;
}
