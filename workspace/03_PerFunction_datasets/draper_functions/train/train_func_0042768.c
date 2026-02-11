rtl8723a_BT_coexist(struct rtw_adapter *padapter)
{
	struct hal_data_8723a *pHalData = GET_HAL_DATA(padapter);

	if (pHalData->bt_coexist.BluetoothCoexist)
		return true;
	else
		return false;
}
