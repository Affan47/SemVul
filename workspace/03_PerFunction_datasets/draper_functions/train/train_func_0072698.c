mwifiex_construct_tdls_action_frame(struct mwifiex_private *priv,
				    const u8 *peer,
				    u8 action_code, u8 dialog_token,
				    u16 status_code, struct sk_buff *skb)
{
	struct ieee80211_mgmt *mgmt;
	u8 bc_addr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	int ret;
	u16 capab;
	struct ieee80211_ht_cap *ht_cap;
	u8 radio, *pos;

	capab = priv->curr_bss_params.bss_descriptor.cap_info_bitmap;

	mgmt = (void *)skb_put(skb, offsetof(struct ieee80211_mgmt, u));

	memset(mgmt, 0, 24);
	memcpy(mgmt->da, peer, ETH_ALEN);
	memcpy(mgmt->sa, priv->curr_addr, ETH_ALEN);
	memcpy(mgmt->bssid, priv->cfg_bssid, ETH_ALEN);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);


	pos = skb_put(skb, ETH_ALEN);

	switch (action_code) {
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		skb_put(skb, sizeof(mgmt->u.action.u.tdls_discover_resp) + 1);
		mgmt->u.action.category = WLAN_CATEGORY_PUBLIC;
		mgmt->u.action.u.tdls_discover_resp.action_code =
					      WLAN_PUB_ACTION_TDLS_DISCOVER_RES;
		mgmt->u.action.u.tdls_discover_resp.dialog_token =
								   dialog_token;
		mgmt->u.action.u.tdls_discover_resp.capability =
							     cpu_to_le16(capab);

		memmove(pos + ETH_ALEN, &mgmt->u.action.category,
			sizeof(mgmt->u.action.u.tdls_discover_resp));

		memcpy(pos, bc_addr, ETH_ALEN);

		ret = mwifiex_tdls_append_rates_ie(priv, skb);
		if (ret) {
			dev_kfree_skb_any(skb);
			return ret;
		}

		pos = (void *)skb_put(skb, sizeof(struct ieee80211_ht_cap) + 2);
		*pos++ = WLAN_EID_HT_CAPABILITY;
		*pos++ = sizeof(struct ieee80211_ht_cap);
		ht_cap = (void *)pos;
		radio = mwifiex_band_to_radio_type(priv->curr_bss_params.band);
		ret = mwifiex_fill_cap_info(priv, radio, ht_cap);
		if (ret) {
			dev_kfree_skb_any(skb);
			return ret;
		}

		if (priv->adapter->is_hw_11ac_capable) {
			ret = mwifiex_tdls_add_vht_capab(priv, skb);
			if (ret) {
				dev_kfree_skb_any(skb);
				return ret;
			}
			mwifiex_tdls_add_aid(priv, skb);
		}

		mwifiex_tdls_add_ext_capab(priv, skb);
		mwifiex_tdls_add_qos_capab(skb);
		break;
	default:
		mwifiex_dbg(priv->adapter, ERROR, "Unknown TDLS action frame type\n");
		return -EINVAL;
	}

	return 0;
}
