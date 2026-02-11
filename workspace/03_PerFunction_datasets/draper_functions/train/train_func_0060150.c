rtl8723a_set_BTCoex_AP_mode_FwRsvdPkt_cmd(struct rtw_adapter *padapter)
{
	struct hal_data_8723a *pHalData;
	u8 bRecover = false;

	DBG_8723A("+%s\n", __func__);

	pHalData = GET_HAL_DATA(padapter);


	if (pHalData->RegFwHwTxQCtrl & BIT(6))
		bRecover = true;


	pHalData->RegFwHwTxQCtrl &= ~BIT(6);
	rtl8723au_write8(padapter, REG_FWHW_TXQ_CTRL + 2,
			 pHalData->RegFwHwTxQCtrl);
	SetFwRsvdPagePkt_BTCoex(padapter);


	if (bRecover) {
		pHalData->RegFwHwTxQCtrl |= BIT(6);
		rtl8723au_write8(padapter, REG_FWHW_TXQ_CTRL + 2,
				 pHalData->RegFwHwTxQCtrl);
	}
}
