EFUSE_ShadowMapUpdate23a(struct rtw_adapter *pAdapter, u8 efuseType)
{
	struct eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(pAdapter);
	u16	mapLen = 0;

	EFUSE_GetEfuseDefinition23a(pAdapter, efuseType,
				 TYPE_EFUSE_MAP_LEN, (void *)&mapLen);

	if (pEEPROM->bautoload_fail_flag == true)
		memset(pEEPROM->efuse_eeprom_data, 0xFF, mapLen);
	else
		Efuse_ReadAllMap(pAdapter, efuseType,
				 pEEPROM->efuse_eeprom_data);
}
