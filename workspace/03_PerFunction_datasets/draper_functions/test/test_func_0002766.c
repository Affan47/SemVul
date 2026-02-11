wlcore_op_channel_switch_beacon(struct ieee80211_hw *hw,
					    struct ieee80211_vif *vif,
					    struct cfg80211_chan_def *chandef)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct ieee80211_channel_switch ch_switch = {
		.block_tx = true,
		.chandef = *chandef,
	};
	int ret;

	wl1271_debug(DEBUG_MAC80211,
		     "mac80211 channel switch beacon (role %d)",
		     wlvif->role_id);

	ret = wlcore_get_csa_count(wl, wlvif, &ch_switch.count);
	if (ret < 0) {
		wl1271_error("error getting beacon (for CSA counter)");
		return;
	}

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EBUSY;
		goto out;
	}

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;

	ret = wl->ops->channel_switch(wl, wlvif, &ch_switch);
	if (ret)
		goto out_sleep;

	set_bit(WLVIF_FLAG_CS_PROGRESS, &wlvif->flags);

out_sleep:
	wl1271_ps_elp_sleep(wl);
out:
	mutex_unlock(&wl->mutex);
}
