BTDM_HWCoexAllOff8723A(struct rtw_adapter *padapter)
{
	struct bt_30info *pBTInfo = GET_BT_INFO(padapter);
	struct bt_mgnt *pBtMgnt = &pBTInfo->BtMgnt;

	if (pBtMgnt->ExtConfig.bManualControl)
		return;

	if (btdm_BtWifiAntNum(padapter) == Ant_x2)
		BTDM_2AntHwCoexAllOff8723A(padapter);
}
