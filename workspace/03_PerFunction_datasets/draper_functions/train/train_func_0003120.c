eprom_get_esi(struct atm_dev *dev)
{
	if (eprom_try_esi(dev,ZEPROM_V1_REG,ZEPROM_V1_ESI_OFF,1)) return;
	(void) eprom_try_esi(dev,ZEPROM_V2_REG,ZEPROM_V2_ESI_OFF,0);
}
