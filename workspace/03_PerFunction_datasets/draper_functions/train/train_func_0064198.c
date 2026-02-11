cfg80211_rtw_disconnect(struct wiphy *wiphy, struct net_device *ndev,
				   u16 reason_code)
{
	struct rtw_adapter *padapter = wiphy_to_adapter(wiphy);

	DBG_8723A("%s(%s)\n", __func__, ndev->name);

	rtw_set_roaming(padapter, 0);

	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) {
		rtw_scan_abort23a(padapter);
		LeaveAllPowerSaveMode23a(padapter);
		rtw_disassoc_cmd23a(padapter, 500, false);

		DBG_8723A("%s...call rtw_indicate_disconnect23a\n", __func__);

		padapter->mlmepriv.not_indic_disco = true;
		rtw_indicate_disconnect23a(padapter);
		padapter->mlmepriv.not_indic_disco = false;

		rtw_free_assoc_resources23a(padapter, 1);
	}

	return 0;
}
