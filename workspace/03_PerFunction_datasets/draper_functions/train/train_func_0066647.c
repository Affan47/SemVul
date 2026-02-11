wl1271_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif;
	struct ieee80211_conf *conf = &hw->conf;
	int ret = 0;

	wl1271_debug(DEBUG_MAC80211, "mac80211 config psm %s power %d %s"
		     " changed 0x%x",
		     conf->flags & IEEE80211_CONF_PS ? "on" : "off",
		     conf->power_level,
		     conf->flags & IEEE80211_CONF_IDLE ? "idle" : "in use",
			 changed);

	mutex_lock(&wl->mutex);

	if (changed & IEEE80211_CONF_CHANGE_POWER)
		wl->power_level = conf->power_level;

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;


	wl12xx_for_each_wlvif(wl, wlvif) {
		ret = wl12xx_config_vif(wl, wlvif, conf, changed);
		if (ret < 0)
			goto out_sleep;
	}

out_sleep:
	wl1271_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);

	return ret;
}
