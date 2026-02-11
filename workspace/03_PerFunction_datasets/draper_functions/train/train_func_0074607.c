btdm_2AntFwDacSwingLvl(struct rtw_adapter *padapter, u8 fwDacSwingLvl)
{
	struct hal_data_8723a *pHalData = GET_HAL_DATA(padapter);
	struct btdm_8723a_2ant *pBtdm8723 = &pHalData->bt_coexist.halCoex8723.btdm2Ant;

	RTPRINT(FBT, BT_TRACE, ("[BTCoex], set FW Dac Swing level = %d\n",  fwDacSwingLvl));
	pBtdm8723->curFwDacSwingLvl = fwDacSwingLvl;


	if (pBtdm8723->preFwDacSwingLvl == pBtdm8723->curFwDacSwingLvl)
		return;

	btdm_SetFwDacSwingLevel(padapter, pBtdm8723->curFwDacSwingLvl);

	pBtdm8723->preFwDacSwingLvl = pBtdm8723->curFwDacSwingLvl;
}
