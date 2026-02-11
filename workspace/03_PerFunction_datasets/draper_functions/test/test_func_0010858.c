update_hw_ht_param(struct rtw_adapter *padapter)
{
	unsigned char max_AMPDU_len;
	unsigned char min_MPDU_spacing;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	DBG_8723A("%s\n", __func__);


	max_AMPDU_len = pmlmeinfo->ht_cap.ampdu_params_info &
		IEEE80211_HT_AMPDU_PARM_FACTOR;

	min_MPDU_spacing = (pmlmeinfo->ht_cap.ampdu_params_info &
			    IEEE80211_HT_AMPDU_PARM_DENSITY) >> 2;

	rtl8723a_set_ampdu_min_space(padapter, min_MPDU_spacing);
	rtl8723a_set_ampdu_factor(padapter, max_AMPDU_len);


	pmlmeinfo->SM_PS = (le16_to_cpu(pmlmeinfo->ht_cap.cap_info) &
			    IEEE80211_HT_CAP_SM_PS) >> 2;
	if (pmlmeinfo->SM_PS == WLAN_HT_CAP_SM_PS_STATIC)
		DBG_8723A("%s(): WLAN_HT_CAP_SM_PS_STATIC\n", __func__);
}
