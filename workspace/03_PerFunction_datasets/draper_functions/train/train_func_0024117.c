mwifiex_check_uap_capabilties(struct mwifiex_private *priv,
					 struct sk_buff *event)
{
	int evt_len;
	u8 *curr;
	u16 tlv_len;
	struct mwifiex_ie_types_data *tlv_hdr;
	struct ieee_types_wmm_parameter *wmm_param_ie = NULL;
	int mask = IEEE80211_WMM_IE_AP_QOSINFO_PARAM_SET_CNT_MASK;

	priv->wmm_enabled = false;
	skb_pull(event, MWIFIEX_BSS_START_EVT_FIX_SIZE);
	evt_len = event->len;
	curr = event->data;

	mwifiex_dbg_dump(priv->adapter, EVT_D, "uap capabilties:",
			 event->data, event->len);

	skb_push(event, MWIFIEX_BSS_START_EVT_FIX_SIZE);

	while ((evt_len >= sizeof(tlv_hdr->header))) {
		tlv_hdr = (struct mwifiex_ie_types_data *)curr;
		tlv_len = le16_to_cpu(tlv_hdr->header.len);

		if (evt_len < tlv_len + sizeof(tlv_hdr->header))
			break;

		switch (le16_to_cpu(tlv_hdr->header.type)) {
		case WLAN_EID_HT_CAPABILITY:
			priv->ap_11n_enabled = true;
			break;

		case WLAN_EID_VHT_CAPABILITY:
			priv->ap_11ac_enabled = true;
			break;

		case WLAN_EID_VENDOR_SPECIFIC:


			wmm_param_ie = (void *)(curr + 2);
			wmm_param_ie->vend_hdr.len = (u8)tlv_len;
			wmm_param_ie->vend_hdr.element_id =
						WLAN_EID_VENDOR_SPECIFIC;
			mwifiex_dbg(priv->adapter, EVENT,
				    "info: check uap capabilities:\t"
				    "wmm parameter set count: %d\n",
				    wmm_param_ie->qos_info_bitmap & mask);

			mwifiex_wmm_setup_ac_downgrade(priv);
			priv->wmm_enabled = true;
			mwifiex_wmm_setup_queue_priorities(priv, wmm_param_ie);
			break;

		default:
			break;
		}

		curr += (tlv_len + sizeof(tlv_hdr->header));
		evt_len -= (tlv_len + sizeof(tlv_hdr->header));
	}

	return 0;
}
