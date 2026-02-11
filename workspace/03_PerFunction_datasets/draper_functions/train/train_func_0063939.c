rtl8723au_hal_deinit(struct rtw_adapter *padapter)
{
	DBG_8723A("==> %s\n", __func__);

#ifdef CONFIG_8723AU_BT_COEXIST
	BT_HaltProcess(padapter);
#endif


	CardDisableRTL8723U(padapter);

	padapter->hw_init_completed = false;

	return _SUCCESS;
}
