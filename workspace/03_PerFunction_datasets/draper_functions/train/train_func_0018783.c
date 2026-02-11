rtl8723a_set_initial_gain(struct rtw_adapter *padapter, u32 rx_gain)
{
	struct hal_data_8723a *pHalData = GET_HAL_DATA(padapter);
	struct dig_t *pDigTable = &pHalData->odmpriv.DM_DigTable;

	if (rx_gain == 0xff)
		ODM_Write_DIG23a(&pHalData->odmpriv, pDigTable->BackupIGValue);
	else {
		pDigTable->BackupIGValue = pDigTable->CurIGValue;
		ODM_Write_DIG23a(&pHalData->odmpriv, rx_gain);
	}
}
