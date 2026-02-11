BTDM_8723ASignalCompensation(struct rtw_adapter *padapter,
			     u8 *rssi_wifi, u8 *rssi_bt)
{
	if (btdm_BtWifiAntNum(padapter) == Ant_x1)
		BTDM_1AntSignalCompensation(padapter, rssi_wifi, rssi_bt);
}
