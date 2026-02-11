rtl8188e_HalDmWatchDog(struct adapter *Adapter)
{
	bool fw_ps_awake = true;
	u8 hw_init_completed = false;
	struct hal_data_8188e *hal_data = GET_HAL_DATA(Adapter);
	struct mlme_priv *pmlmepriv = NULL;
	u8 bLinked = false;

	hw_init_completed = Adapter->hw_init_completed;

	if (!hw_init_completed)
		goto skip_dm;

	rtw_hal_get_hwreg(Adapter, HW_VAR_FWLPS_RF_ON, (u8 *)(&fw_ps_awake));


	if (Adapter->wdinfo.p2p_ps_mode)
		fw_ps_awake = false;


	pmlmepriv = &Adapter->mlmepriv;

	if ((check_fwstate(pmlmepriv, WIFI_AP_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE |
			   WIFI_ADHOC_MASTER_STATE))) {
		if (Adapter->stapriv.asoc_sta_count > 2)
			bLinked = true;
	} else {
		if (check_fwstate(pmlmepriv, _FW_LINKED))
			bLinked = true;
	}

	ODM_CmnInfoUpdate(&hal_data->odmpriv, ODM_CMNINFO_LINK, bLinked);
	ODM_DMWatchdog(&hal_data->odmpriv);
skip_dm:


	return;
}
