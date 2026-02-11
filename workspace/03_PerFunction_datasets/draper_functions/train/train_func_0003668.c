r8711_wx_get_name(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	u32 ht_ielen = 0;
	char *p;
	u8 ht_cap = false;
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	u8 *prates;

	if (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE) ==
	    true) {

		p = r8712_get_ie(&pcur_bss->IEs[12], _HT_CAPABILITY_IE_,
				 &ht_ielen, pcur_bss->IELength - 12);
		if (p && ht_ielen > 0)
			ht_cap = true;
		prates = pcur_bss->rates;
		if (r8712_is_cckratesonly_included(prates)) {
			if (ht_cap)
				snprintf(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11bn");
			else
				snprintf(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11b");
		} else if (r8712_is_cckrates_included(prates)) {
			if (ht_cap)
				snprintf(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11bgn");
			else
				snprintf(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11bg");
		} else {
			if (ht_cap)
				snprintf(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11gn");
			else
				snprintf(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11g");
		}
	} else {
		snprintf(wrqu->name, IFNAMSIZ, "unassociated");
	}
	return 0;
}
