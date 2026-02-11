iwl_mvm_mac_get_queues_mask(struct ieee80211_vif *vif)
{
	u32 qmask = 0, ac;

	if (vif->type == NL80211_IFTYPE_P2P_DEVICE)
		return BIT(IWL_MVM_OFFCHANNEL_QUEUE);

	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		if (vif->hw_queue[ac] != IEEE80211_INVAL_HW_QUEUE)
			qmask |= BIT(vif->hw_queue[ac]);
	}

	if (vif->type == NL80211_IFTYPE_AP)
		qmask |= BIT(vif->cab_queue);

	return qmask;
}
