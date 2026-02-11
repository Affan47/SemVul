rt2x00lib_beaconupdate_iter(void *data, u8 *mac,
					struct ieee80211_vif *vif)
{
	struct rt2x00_dev *rt2x00dev = data;

	if (vif->type != NL80211_IFTYPE_AP &&
	    vif->type != NL80211_IFTYPE_ADHOC &&
	    vif->type != NL80211_IFTYPE_MESH_POINT &&
	    vif->type != NL80211_IFTYPE_WDS)
		return;


	WARN_ON(rt2x00_is_usb(rt2x00dev));
	rt2x00queue_update_beacon(rt2x00dev, vif);
}
