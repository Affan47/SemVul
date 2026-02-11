Hal_EfuseParseThermalMeter_8723A(struct rtw_adapter *padapter,
				 u8 *PROMContent, bool AutoloadFail)
{
	struct hal_data_8723a *pHalData = GET_HAL_DATA(padapter);


	if (!AutoloadFail)
		pHalData->EEPROMThermalMeter =
		    PROMContent[EEPROM_THERMAL_METER_8723A];
	else
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter;

	if ((pHalData->EEPROMThermalMeter == 0xff) || AutoloadFail) {
		pHalData->bAPKThermalMeterIgnore = true;
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter;
	}

	DBG_8723A("%s: ThermalMeter = 0x%x\n", __func__,
		  pHalData->EEPROMThermalMeter);
}
