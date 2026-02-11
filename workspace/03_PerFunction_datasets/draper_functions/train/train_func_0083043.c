rtw_restructure_ht_ie23a(struct rtw_adapter *padapter, u8 *in_ie,
			      u8 *out_ie, uint in_len, uint *pout_len)
{
	u32 out_len;
	int max_rx_ampdu_factor;
	unsigned char *pframe;
	const u8 *p;
	struct ieee80211_ht_cap ht_capie;
	u8 WMM_IE[7] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00};
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;

	phtpriv->ht_option = false;

	p = cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, in_ie, in_len);

	if (p && p[1] > 0) {
		u32 rx_packet_offset, max_recvbuf_sz;

		if (pmlmepriv->qos_option == 0) {
			out_len = *pout_len;
			pframe = rtw_set_ie23a(out_ie + out_len,
					       WLAN_EID_VENDOR_SPECIFIC,
					       sizeof(WMM_IE), WMM_IE,
					       pout_len);

			pmlmepriv->qos_option = 1;
		}

		out_len = *pout_len;

		memset(&ht_capie, 0, sizeof(struct ieee80211_ht_cap));

		ht_capie.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
			IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40 |
			IEEE80211_HT_CAP_TX_STBC | IEEE80211_HT_CAP_DSSSCCK40);

		GetHalDefVar8192CUsb(padapter, HAL_DEF_RX_PACKET_OFFSET,
				     &rx_packet_offset);
		GetHalDefVar8192CUsb(padapter, HAL_DEF_MAX_RECVBUF_SZ,
				     &max_recvbuf_sz);

		GetHalDefVar8192CUsb(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR,
				     &max_rx_ampdu_factor);
		ht_capie.ampdu_params_info = max_rx_ampdu_factor & 0x03;

		if (padapter->securitypriv.dot11PrivacyAlgrthm ==
		    WLAN_CIPHER_SUITE_CCMP)
			ht_capie.ampdu_params_info |=
				(IEEE80211_HT_AMPDU_PARM_DENSITY& (0x07 << 2));
		else
			ht_capie.ampdu_params_info |=
				(IEEE80211_HT_AMPDU_PARM_DENSITY & 0x00);

		pframe = rtw_set_ie23a(out_ie + out_len, WLAN_EID_HT_CAPABILITY,
				    sizeof(struct ieee80211_ht_cap),
				    (unsigned char *)&ht_capie, pout_len);

		phtpriv->ht_option = true;

		p = cfg80211_find_ie(WLAN_EID_HT_OPERATION, in_ie, in_len);
		if (p && (p[1] == sizeof(struct ieee80211_ht_operation))) {
			out_len = *pout_len;
			pframe = rtw_set_ie23a(out_ie + out_len,
					       WLAN_EID_HT_OPERATION,
					       p[1], p + 2 , pout_len);
		}
	}

	return phtpriv->ht_option;
}
