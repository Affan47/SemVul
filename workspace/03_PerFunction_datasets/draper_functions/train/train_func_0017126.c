iwl_mvm_send_rm_bcast_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	lockdep_assert_held(&mvm->mutex);

	ret = iwl_mvm_rm_sta_common(mvm, mvmvif->bcast_sta.sta_id);
	if (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");
	return ret;
}
