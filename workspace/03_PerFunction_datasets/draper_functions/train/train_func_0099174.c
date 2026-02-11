cw1200_add_interface(struct ieee80211_hw *dev,
			 struct ieee80211_vif *vif)
{
	int ret;
	struct cw1200_common *priv = dev->priv;


	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	mutex_lock(&priv->conf_mutex);

	if (priv->mode != NL80211_IFTYPE_MONITOR) {
		mutex_unlock(&priv->conf_mutex);
		return -EOPNOTSUPP;
	}

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		priv->mode = vif->type;
		break;
	default:
		mutex_unlock(&priv->conf_mutex);
		return -EOPNOTSUPP;
	}

	priv->vif = vif;
	memcpy(priv->mac_addr, vif->addr, ETH_ALEN);
	ret = cw1200_setup_mac(priv);


	mutex_unlock(&priv->conf_mutex);
	return ret;
}
