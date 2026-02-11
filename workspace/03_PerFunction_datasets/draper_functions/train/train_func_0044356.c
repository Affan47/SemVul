ath6kl_mgmt_tx(struct wiphy *wiphy, struct wireless_dev *wdev,
			  struct cfg80211_mgmt_tx_params *params, u64 *cookie)
{
	struct ath6kl_vif *vif = ath6kl_vif_from_wdev(wdev);
	struct ath6kl *ar = ath6kl_priv(vif->ndev);
	struct ieee80211_channel *chan = params->chan;
	const u8 *buf = params->buf;
	size_t len = params->len;
	unsigned int wait = params->wait;
	bool no_cck = params->no_cck;
	u32 id, freq;
	const struct ieee80211_mgmt *mgmt;
	bool more_data, queued;


	freq = vif->ch_hint;
	if (chan)
		freq = chan->center_freq;


	if (WARN_ON(freq == 0))
		return -EINVAL;

	mgmt = (const struct ieee80211_mgmt *) buf;
	if (vif->nw_type == AP_NETWORK && test_bit(CONNECTED, &vif->flags) &&
	    ieee80211_is_probe_resp(mgmt->frame_control) &&
	    ath6kl_is_p2p_go_ssid(buf, len)) {


		*cookie = 0;
		return ath6kl_send_go_probe_resp(vif, buf, len, freq);
	}

	id = vif->send_action_id++;
	if (id == 0) {


		id = vif->send_action_id++;
	}

	*cookie = id;


	if (vif->nw_type == AP_NETWORK) {
		queued = ath6kl_mgmt_powersave_ap(vif, id, freq, wait, buf, len,
						  &more_data, no_cck);
		if (queued)
			return 0;
	}

	return ath6kl_wmi_send_mgmt_cmd(ar->wmi, vif->fw_vif_idx, id, freq,
					wait, buf, len, no_cck);
}
