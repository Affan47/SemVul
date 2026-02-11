rtw_createbss_cmd_callback(struct adapter *padapter, struct cmd_obj *pcmd)
{
	struct sta_info *psta = NULL;
	struct wlan_network *pwlan = NULL;
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct wlan_bssid_ex *pnetwork = (struct wlan_bssid_ex *)pcmd->parmbuf;
	struct wlan_network *tgt_network = &(pmlmepriv->cur_network);


	if (pcmd->res != H2C_SUCCESS) {
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\n ********Error: rtw_createbss_cmd_callback  Fail ************\n\n."));
		mod_timer(&pmlmepriv->assoc_timer,
			  jiffies + msecs_to_jiffies(1));
	}

	del_timer_sync(&pmlmepriv->assoc_timer);

	spin_lock_bh(&pmlmepriv->lock);

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		psta = rtw_get_stainfo(&padapter->stapriv, pnetwork->MacAddress);
		if (!psta) {
			psta = rtw_alloc_stainfo(&padapter->stapriv, pnetwork->MacAddress);
			if (psta == NULL) {
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\nCan't alloc sta_info when createbss_cmd_callback\n"));
				goto createbss_cmd_fail;
			}
		}

		rtw_indicate_connect(padapter);
	} else {
		pwlan = _rtw_alloc_network(pmlmepriv);
		spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
		if (pwlan == NULL) {
			pwlan = rtw_get_oldest_wlan_network(&pmlmepriv->scanned_queue);
			if (pwlan == NULL) {
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\n Error:  can't get pwlan in rtw_joinbss_event_callback\n"));
				spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
				goto createbss_cmd_fail;
			}
			pwlan->last_scanned = jiffies;
		} else {
			list_add_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue);
		}

		pnetwork->Length = get_wlan_bssid_ex_sz(pnetwork);
		memcpy(&(pwlan->network), pnetwork, pnetwork->Length);

		memcpy(&tgt_network->network, pnetwork, (get_wlan_bssid_ex_sz(pnetwork)));

		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);

	}

createbss_cmd_fail:

	spin_unlock_bh(&pmlmepriv->lock);

	rtw_free_cmd_obj(pcmd);

}
