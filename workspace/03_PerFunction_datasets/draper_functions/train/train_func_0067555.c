BTDM_1AntSignalCompensation(struct rtw_adapter *padapter,
				 u8 *rssi_wifi, u8 *rssi_bt)
{
	struct hal_data_8723a *pHalData;
	struct btdm_8723a_1ant *pBtdm8723;
	u8 RSSI_WiFi_Cmpnstn, RSSI_BT_Cmpnstn;

	pHalData = GET_HAL_DATA(padapter);
	pBtdm8723 = &pHalData->bt_coexist.halCoex8723.btdm1Ant;
	RSSI_WiFi_Cmpnstn = 0;
	RSSI_BT_Cmpnstn = 0;

	switch (pBtdm8723->curPsTdma) {
	case 1:
		RSSI_WiFi_Cmpnstn = 11;
		break;
	case 2:
		RSSI_WiFi_Cmpnstn = 14;
		break;
	case 9:
		RSSI_WiFi_Cmpnstn = 18;
		break;
	case 11:
		RSSI_WiFi_Cmpnstn = 20;
		break;
	case 4:
		RSSI_WiFi_Cmpnstn = 17;
		break;
	case 16:
		RSSI_WiFi_Cmpnstn = 18;
		break;
	case 18:
		RSSI_WiFi_Cmpnstn = 14;
		break;
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 33:
		RSSI_WiFi_Cmpnstn = 22;
		break;
	default:
		break;
	}

	if (rssi_wifi && RSSI_WiFi_Cmpnstn) {
		RTPRINT(FBT, BT_TRACE,
			("[BTCoex], 1AntSgnlCmpnstn, case %d, WiFiCmpnstn "
			 "=%d(%d => %d)\n", pBtdm8723->curPsTdma,
			 RSSI_WiFi_Cmpnstn, *rssi_wifi,
			 *rssi_wifi+RSSI_WiFi_Cmpnstn));
		*rssi_wifi += RSSI_WiFi_Cmpnstn;
	}

	if (rssi_bt && RSSI_BT_Cmpnstn) {
		RTPRINT(FBT, BT_TRACE,
			("[BTCoex], 1AntSgnlCmpnstn, case %d, BTCmpnstn "
			 "=%d(%d => %d)\n", pBtdm8723->curPsTdma,
			 RSSI_BT_Cmpnstn, *rssi_bt, *rssi_bt+RSSI_BT_Cmpnstn));
		*rssi_bt += RSSI_BT_Cmpnstn;
	}
}
