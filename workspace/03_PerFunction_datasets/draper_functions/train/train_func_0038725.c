rtw_suspend(struct usb_interface *pusb_intf, pm_message_t message)
{
	struct dvobj_priv *dvobj = usb_get_intfdata(pusb_intf);
	struct rtw_adapter *padapter = dvobj->if1;
	struct net_device *pnetdev = padapter->pnetdev;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	int ret = 0;
	unsigned long start_time = jiffies;

	DBG_8723A("==> %s (%s:%d)\n", __func__, current->comm, current->pid);

	if ((!padapter->bup) || (padapter->bDriverStopped) ||
	    (padapter->bSurpriseRemoved)) {
		DBG_8723A("padapter->bup =%d bDriverStopped =%d bSurpriseRemoved = %d\n",
			  padapter->bup, padapter->bDriverStopped,
			  padapter->bSurpriseRemoved);
		goto exit;
	}
	pwrpriv->bInSuspend = true;
	rtw_cancel_all_timer23a(padapter);
	LeaveAllPowerSaveMode23a(padapter);

	down(&pwrpriv->lock);


	if (pnetdev) {
		netif_carrier_off(pnetdev);
		netif_tx_stop_all_queues(pnetdev);
	}


	rtw_disassoc_cmd23a(padapter, 0, false);

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE) &&
	    check_fwstate(pmlmepriv, _FW_LINKED)) {
		DBG_8723A("%s:%d %s(%pM), length:%d assoc_ssid.length:%d\n",
			  __func__, __LINE__,
			  pmlmepriv->cur_network.network.Ssid.ssid,
			  pmlmepriv->cur_network.network.MacAddress,
			  pmlmepriv->cur_network.network.Ssid.ssid_len,
			  pmlmepriv->assoc_ssid.ssid_len);

		rtw_set_roaming(padapter, 1);
	}

	rtw_indicate_disconnect23a(padapter);

	rtw_free_assoc_resources23a(padapter, 1);

	rtw_free_network_queue23a(padapter);

	rtw_dev_unload(padapter);
	up(&pwrpriv->lock);

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		rtw_cfg80211_indicate_scan_done(
			wdev_to_priv(padapter->rtw_wdev), true);

	if (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		rtw_indicate_disconnect23a(padapter);

exit:
	DBG_8723A("<===  %s return %d.............. in %dms\n", __func__,
		  ret, jiffies_to_msecs(jiffies - start_time));

	return ret;
}
