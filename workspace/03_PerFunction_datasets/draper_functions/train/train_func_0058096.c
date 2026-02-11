iwl_mvm_rm_sta_id(struct iwl_mvm *mvm,
		      struct ieee80211_vif *vif,
		      u8 sta_id)
{
	int ret = iwl_mvm_rm_sta_common(mvm, sta_id);

	lockdep_assert_held(&mvm->mutex);

	RCU_INIT_POINTER(mvm->fw_id_to_mac_id[sta_id], NULL);
	return ret;
}
