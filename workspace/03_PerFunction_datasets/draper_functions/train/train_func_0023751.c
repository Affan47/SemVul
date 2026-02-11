ath_ahb_eeprom_read(struct ath_common *common, u32 off, u16 *data)
{
	struct ath_softc *sc = (struct ath_softc *)common->priv;
	struct platform_device *pdev = to_platform_device(sc->dev);
	struct ath9k_platform_data *pdata;

	pdata = dev_get_platdata(&pdev->dev);
	if (off >= (ARRAY_SIZE(pdata->eeprom_data))) {
		ath_err(common,
			"%s: flash read failed, offset %08x is out of range\n",
			__func__, off);
		return false;
	}

	*data = pdata->eeprom_data[off];
	return true;
}
