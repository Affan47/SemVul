join_cmd_hdl23a(struct rtw_adapter *padapter, const u8 *pbuf)
{
	struct registry_priv *pregpriv = &padapter->registrypriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	const struct wlan_bssid_ex *pparm = (struct wlan_bssid_ex *)pbuf;
	struct ieee80211_ht_operation *pht_info;
	u32 i;
	u8 *p;


	if (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS) {
		if (pmlmeinfo->state & MSR_INFRA)
			issue_deauth_ex(padapter, pnetwork->MacAddress,
					WLAN_REASON_DEAUTH_LEAVING, 5, 100);

		pmlmeinfo->state = MSR_NOLINK;


		flush_all_cam_entry23a(padapter);

		del_timer_sync(&pmlmeext->link_timer);


		rtl8723a_set_media_status(padapter, MSR_INFRA);

		hw_var_set_mlme_disconnect(padapter);
	}

	rtw_joinbss_reset23a(padapter);

	pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
	pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pmlmeinfo->ERP_enable = 0;
	pmlmeinfo->WMM_enable = 0;
	pmlmeinfo->HT_enable = 0;
	pmlmeinfo->HT_caps_enable = 0;
	pmlmeinfo->HT_info_enable = 0;
	pmlmeinfo->bwmode_updated = false;


	if (pparm->IELength > MAX_IE_SZ)
		return H2C_PARAMETERS_ERROR;

	memcpy(pnetwork, pbuf, sizeof(struct wlan_bssid_ex));


	for (i = 0; i < pnetwork->IELength;) {
		p = pnetwork->IEs + i;

		switch (p[0]) {
		case WLAN_EID_VENDOR_SPECIFIC:
			if (!memcmp(p + 2, WMM_OUI23A, 4))
				pmlmeinfo->WMM_enable = 1;
			break;

		case WLAN_EID_HT_CAPABILITY:
			pmlmeinfo->HT_caps_enable = 1;
			break;

		case WLAN_EID_HT_OPERATION:
			pmlmeinfo->HT_info_enable = 1;


			pht_info = (struct ieee80211_ht_operation *)(p + 2);

			if (pregpriv->cbw40_enable &&
			    (pht_info->ht_param &
			     IEEE80211_HT_PARAM_CHAN_WIDTH_ANY)) {

				pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_40;
				switch (pht_info->ht_param &
					IEEE80211_HT_PARAM_CHA_SEC_OFFSET) {
				case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
					pmlmeext->cur_ch_offset =
						HAL_PRIME_CHNL_OFFSET_LOWER;
					break;

				case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
					pmlmeext->cur_ch_offset =
						HAL_PRIME_CHNL_OFFSET_UPPER;
					break;

				default:
					pmlmeext->cur_ch_offset =
						HAL_PRIME_CHNL_OFFSET_DONT_CARE;
					break;
				}

				DBG_8723A("set ch/bw before connected\n");
			}
			break;

		default:
			break;
		}

		i += (p[1] + 2);
	}

	hw_var_set_bssid(padapter, pmlmeinfo->network.MacAddress);
	hw_var_set_mlme_join(padapter, 0);


	del_timer_sync(&pmlmeext->link_timer);

	start_clnt_join(padapter);

	return H2C_SUCCESS;
}
