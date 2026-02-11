rtw_init_mlme_priv23a(struct rtw_adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	pmlmepriv->nic_hdl = padapter;

	pmlmepriv->fw_state = 0;
	pmlmepriv->cur_network.network.ifmode = NL80211_IFTYPE_UNSPECIFIED;


	pmlmepriv->scan_mode = SCAN_ACTIVE;

	spin_lock_init(&pmlmepriv->lock);
	_rtw_init_queue23a(&pmlmepriv->scanned_queue);

	memset(&pmlmepriv->assoc_ssid, 0, sizeof(struct cfg80211_ssid));

	rtw_clear_scan_deny(padapter);

	rtw_init_mlme_timer(padapter);
	return _SUCCESS;
}
