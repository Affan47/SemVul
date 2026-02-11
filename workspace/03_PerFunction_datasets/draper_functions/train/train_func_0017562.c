rtw_restructure_ht_ie(struct adapter *padapter, u8 *in_ie, u8 *out_ie, uint in_len, uint *pout_len)
{
	u32 ielen, out_len;
	enum ht_cap_ampdu_factor max_rx_ampdu_factor;
	unsigned char *p;
	struct rtw_ieee80211_ht_cap ht_capie;
	unsigned char WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00};
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct qos_priv		*pqospriv = &pmlmepriv->qospriv;
	struct ht_priv		*phtpriv = &pmlmepriv->htpriv;
	u32 rx_packet_offset, max_recvbuf_sz;


	phtpriv->ht_option = false;

	p = rtw_get_ie(in_ie+12, _HT_CAPABILITY_IE_, &ielen, in_len-12);

	if (p && ielen > 0) {
		if (pqospriv->qos_option == 0) {
			out_len = *pout_len;
			rtw_set_ie(out_ie+out_len, _VENDOR_SPECIFIC_IE_,
				   _WMM_IE_Length_, WMM_IE, pout_len);

			pqospriv->qos_option = 1;
		}

		out_len = *pout_len;

		memset(&ht_capie, 0, sizeof(struct rtw_ieee80211_ht_cap));

		ht_capie.cap_info = IEEE80211_HT_CAP_SUP_WIDTH |
				    IEEE80211_HT_CAP_SGI_20 |
				    IEEE80211_HT_CAP_SGI_40 |
				    IEEE80211_HT_CAP_TX_STBC |
				    IEEE80211_HT_CAP_DSSSCCK40;

		rtw_hal_get_def_var(padapter, HAL_DEF_RX_PACKET_OFFSET, &rx_packet_offset);
		rtw_hal_get_def_var(padapter, HAL_DEF_MAX_RECVBUF_SZ, &max_recvbuf_sz);


		rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor);
		ht_capie.ampdu_params_info = (max_rx_ampdu_factor&0x03);

		if (padapter->securitypriv.dot11PrivacyAlgrthm == _AES_)
			ht_capie.ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&(0x07<<2));
		else
			ht_capie.ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&0x00);


		rtw_set_ie(out_ie+out_len, _HT_CAPABILITY_IE_,
			   sizeof(struct rtw_ieee80211_ht_cap), (unsigned char *)&ht_capie, pout_len);

		phtpriv->ht_option = true;

		p = rtw_get_ie(in_ie+12, _HT_ADD_INFO_IE_, &ielen, in_len-12);
		if (p && (ielen == sizeof(struct ieee80211_ht_addt_info))) {
			out_len = *pout_len;
			rtw_set_ie(out_ie+out_len, _HT_ADD_INFO_IE_, ielen, p+2, pout_len);
		}
	}
	return phtpriv->ht_option;
}
