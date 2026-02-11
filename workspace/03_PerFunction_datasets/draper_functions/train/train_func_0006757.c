wl1271_op_set_default_key_idx(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif,
					  int key_idx)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set default key idx %d",
		     key_idx);


	if (key_idx == -1)
		return;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EAGAIN;
		goto out_unlock;
	}

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out_unlock;

	wlvif->default_key = key_idx;


	if (wlvif->encryption_type == KEY_WEP) {
		ret = wl12xx_cmd_set_default_wep_key(wl,
				key_idx,
				wlvif->sta.hlid);
		if (ret < 0)
			goto out_sleep;
	}

out_sleep:
	wl1271_ps_elp_sleep(wl);

out_unlock:
	mutex_unlock(&wl->mutex);
}
