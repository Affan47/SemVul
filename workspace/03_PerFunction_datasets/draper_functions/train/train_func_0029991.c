rtl8723a_BT_do_coexist(struct rtw_adapter *padapter)
{
	struct hal_data_8723a *pHalData = GET_HAL_DATA(padapter);

	if (!rtl8723a_BT_coexist(padapter)) {
		RTPRINT(FBT, BT_TRACE, ("[DM][BT], BT not exists!!\n"));
		return;
	}

	if (!pHalData->bt_coexist.bInitlized) {
		RTPRINT(FBT, BT_TRACE, ("[DM][BT], btdm_InitBtCoexistDM()\n"));
		btdm_InitBtCoexistDM(padapter);
	}

	RTPRINT(FBT, BT_TRACE, ("\n\n[DM][BT], BTDM start!!\n"));

	BTDM_PWDBMonitor(padapter);

	RTPRINT(FBT, BT_TRACE, ("[DM][BT], HW type is 8723\n"));
	BTDM_BTCoexist8723A(padapter);
	RTPRINT(FBT, BT_TRACE, ("[DM][BT], BTDM end!!\n\n"));
}
