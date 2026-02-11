iwl_mvm_disallow_offloading(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif,
					struct iwl_d0i3_iter_data *iter_data)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct ieee80211_sta *ap_sta;
	struct iwl_mvm_sta *mvmsta;
	u32 available_tids = 0;
	u8 tid;

	if (WARN_ON(vif->type != NL80211_IFTYPE_STATION ||
		    mvmvif->ap_sta_id == IWL_MVM_STATION_COUNT))
		return false;

	ap_sta = rcu_dereference(mvm->fw_id_to_mac_id[mvmvif->ap_sta_id]);
	if (IS_ERR_OR_NULL(ap_sta))
		return false;

	mvmsta = iwl_mvm_sta_from_mac80211(ap_sta);
	spin_lock_bh(&mvmsta->lock);
	for (tid = 0; tid < IWL_MAX_TID_COUNT; tid++) {
		struct iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];


		if (iwl_mvm_tid_queued(tid_data))
			continue;

		if (tid_data->state != IWL_AGG_OFF)
			continue;

		available_tids |= BIT(tid);
	}
	spin_unlock_bh(&mvmsta->lock);


	if (!available_tids)
		return true;


	iter_data->offloading_tid = ffs(available_tids) - 1;
	return false;
}
