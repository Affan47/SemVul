mt7601u_eeprom_init(struct mt7601u_dev *dev)
{
	u8 *eeprom;
	int i, ret;

	ret = mt7601u_efuse_physical_size_check(dev);
	if (ret)
		return ret;

	dev->ee = devm_kzalloc(dev->dev, sizeof(*dev->ee), GFP_KERNEL);
	if (!dev->ee)
		return -ENOMEM;

	eeprom = kmalloc(MT7601U_EEPROM_SIZE, GFP_KERNEL);
	if (!eeprom)
		return -ENOMEM;

	for (i = 0; i + 16 <= MT7601U_EEPROM_SIZE; i += 16) {
		ret = mt7601u_efuse_read(dev, i, eeprom + i, MT_EE_READ);
		if (ret)
			goto out;
	}

	if (eeprom[MT_EE_VERSION_EE] > MT7601U_EE_MAX_VER)
		dev_warn(dev->dev,
			 "Warning: unsupported EEPROM version %02hhx\n",
			 eeprom[MT_EE_VERSION_EE]);
	dev_info(dev->dev, "EEPROM ver:%02hhx fae:%02hhx\n",
		 eeprom[MT_EE_VERSION_EE], eeprom[MT_EE_VERSION_FAE]);

	mt7601u_set_macaddr(dev, eeprom);
	mt7601u_set_chip_cap(dev, eeprom);
	mt7601u_set_channel_power(dev, eeprom);
	mt7601u_set_country_reg(dev, eeprom);
	mt7601u_set_rf_freq_off(dev, eeprom);
	mt7601u_set_rssi_offset(dev, eeprom);
	dev->ee->ref_temp = eeprom[MT_EE_REF_TEMP];
	dev->ee->lna_gain = eeprom[MT_EE_LNA_GAIN];

	mt7601u_config_tx_power_per_rate(dev, eeprom);

	mt7601u_init_tssi_params(dev, eeprom);
out:
	kfree(eeprom);
	return ret;
}
