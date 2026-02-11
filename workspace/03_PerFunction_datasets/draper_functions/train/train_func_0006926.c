_linked_rx_signal_strehgth_display(struct adapter *padapter)
{
	struct mlme_ext_priv    *pmlmeext = &padapter->mlmeextpriv;
      struct mlme_ext_info    *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 mac_id;
	int UndecoratedSmoothedPWDB;
	if ((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE)
		mac_id = 0;
	else if ((pmlmeinfo->state&0x03) == _HW_STATE_AP_)
		mac_id = 2;

	rtw_hal_get_def_var(padapter, HW_DEF_RA_INFO_DUMP, &mac_id);

	rtw_hal_get_def_var(padapter, HAL_DEF_UNDERCORATEDSMOOTHEDPWDB, &UndecoratedSmoothedPWDB);
	DBG_88E("UndecoratedSmoothedPWDB:%d\n", UndecoratedSmoothedPWDB);
}
