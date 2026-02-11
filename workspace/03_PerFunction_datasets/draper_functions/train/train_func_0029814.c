wl1251_op_add_interface(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct wl1251 *wl = hw->priv;
	int ret = 0;

	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	wl1251_debug(DEBUG_MAC80211, "mac80211 add interface type %d mac %pM",
		     vif->type, vif->addr);

	mutex_lock(&wl->mutex);
	if (wl->vif) {
		ret = -EBUSY;
		goto out;
	}

	wl->vif = vif;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		wl->bss_type = BSS_TYPE_STA_BSS;
		break;
	case NL80211_IFTYPE_ADHOC:
		wl->bss_type = BSS_TYPE_IBSS;
		break;
	default:
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (!ether_addr_equal_unaligned(wl->mac_addr, vif->addr)) {
		memcpy(wl->mac_addr, vif->addr, ETH_ALEN);
		SET_IEEE80211_PERM_ADDR(wl->hw, wl->mac_addr);
		ret = wl1251_acx_station_id(wl);
		if (ret < 0)
			goto out;
	}

out:
	mutex_unlock(&wl->mutex);
	return ret;
}
