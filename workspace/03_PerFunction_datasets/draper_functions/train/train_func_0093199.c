ath9k_htc_beacon_config(struct ath9k_htc_priv *priv,
			     struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath_beacon_config *cur_conf = &priv->cur_beacon_conf;
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	struct ath9k_htc_vif *avp = (struct ath9k_htc_vif *) vif->drv_priv;

	if (!ath9k_htc_check_beacon_config(priv, vif))
		return;

	cur_conf->beacon_interval = bss_conf->beacon_int;
	if (cur_conf->beacon_interval == 0)
		cur_conf->beacon_interval = 100;

	cur_conf->dtim_period = bss_conf->dtim_period;
	cur_conf->bmiss_timeout =
		ATH_DEFAULT_BMISS_LIMIT * cur_conf->beacon_interval;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(priv, cur_conf);
		avp->beacon_configured = true;
		break;
	case NL80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(priv, cur_conf);
		break;
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(priv, cur_conf);
		break;
	default:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		return;
	}
}
