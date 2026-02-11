iwl_mvm_config_iface_filter(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					unsigned int filter_flags,
					unsigned int changed_flags)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);


	if (!(changed_flags & FIF_PROBE_REQ))
		return;


	if (vif->type != NL80211_IFTYPE_STATION || !vif->bss_conf.assoc ||
	    !vif->p2p)
		return;

	mutex_lock(&mvm->mutex);
	iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
	mutex_unlock(&mvm->mutex);
}
