rtl8723a_BT_disable_EDCA_turbo(struct rtw_adapter *padapter)
{
	struct bt_mgnt *pBtMgnt;
	struct hal_data_8723a *pHalData;
	u8 bBtChangeEDCA = false;
	u32 EDCA_BT_BE = 0x5ea42b, cur_EDCA_reg;
	bool bRet = false;

	pHalData = GET_HAL_DATA(padapter);
	pBtMgnt = &pHalData->BtInfo.BtMgnt;

	if (!rtl8723a_BT_coexist(padapter)) {
		bRet = false;
		pHalData->bt_coexist.lastBtEdca = 0;
		return bRet;
	}
	if (!((pBtMgnt->bSupportProfile) ||
	    (pHalData->bt_coexist.BT_CoexistType == BT_CSR_BC8))) {
		bRet = false;
		pHalData->bt_coexist.lastBtEdca = 0;
		return bRet;
	}

	if (rtl8723a_BT_using_antenna_1(padapter)) {
		bRet = false;
		pHalData->bt_coexist.lastBtEdca = 0;
		return bRet;
	}

	if (pHalData->bt_coexist.exec_cnt < 3)
		pHalData->bt_coexist.exec_cnt++;
	else
		pHalData->bt_coexist.bEDCAInitialized = true;


	if (!(pHalData->bt_coexist.CurrentState & BT_COEX_STATE_BT_IDLE)) {
		RTPRINT(FBT, BT_TRACE, ("BT state non idle, set bt EDCA\n"));


		if (pHalData->odmpriv.DM_EDCA_Table.bCurrentTurboEDCA) {
			bBtChangeEDCA = true;
			pHalData->odmpriv.DM_EDCA_Table.bCurrentTurboEDCA = false;
			pHalData->dmpriv.prv_traffic_idx = 3;
		}
		cur_EDCA_reg = rtl8723au_read32(padapter, REG_EDCA_BE_PARAM);

		if (cur_EDCA_reg != EDCA_BT_BE)
			bBtChangeEDCA = true;
		if (bBtChangeEDCA || !pHalData->bt_coexist.bEDCAInitialized) {
			rtl8723au_write32(padapter, REG_EDCA_BE_PARAM,
					  EDCA_BT_BE);
			pHalData->bt_coexist.lastBtEdca = EDCA_BT_BE;
		}
		bRet = true;
	} else {
		RTPRINT(FBT, BT_TRACE, ("BT state idle, set original EDCA\n"));
		pHalData->bt_coexist.lastBtEdca = 0;
		bRet = false;
	}
	return bRet;
}
