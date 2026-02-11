iwl_mvm_mac_conf_tx(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif, u16 ac,
			       const struct ieee80211_tx_queue_params *params)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	mvmvif->queue_params[ac] = *params;


	if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {
		int ret;

		mutex_lock(&mvm->mutex);
		ret = iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
		mutex_unlock(&mvm->mutex);
		return ret;
	}
	return 0;
}
