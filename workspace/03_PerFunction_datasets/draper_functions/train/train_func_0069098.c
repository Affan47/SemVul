iwl_mvm_power_uapsd_misbehav_ap_iterator(void *_data, u8 *mac,
						     struct ieee80211_vif *vif)
{
	u8 *ap_sta_id = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);


	if (mvmvif->ap_sta_id == *ap_sta_id)
		memcpy(mvmvif->uapsd_misbehaving_bssid, vif->bss_conf.bssid,
		       ETH_ALEN);
}
