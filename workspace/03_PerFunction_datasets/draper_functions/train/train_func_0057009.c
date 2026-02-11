_iwl_mvm_enable_beacon_filter(struct iwl_mvm *mvm,
					 struct ieee80211_vif *vif,
					 struct iwl_beacon_filter_cmd *cmd,
					 u32 cmd_flags,
					 bool d0i3)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	if (mvmvif != mvm->bf_allowed_vif || !vif->bss_conf.dtim_period ||
	    vif->type != NL80211_IFTYPE_STATION || vif->p2p)
		return 0;

	iwl_mvm_beacon_filter_set_cqm_params(mvm, vif, cmd, d0i3);
	if (!d0i3)
		iwl_mvm_beacon_filter_debugfs_parameters(vif, cmd);
	ret = iwl_mvm_beacon_filter_send_cmd(mvm, cmd, cmd_flags);


	if (!ret && !d0i3)
		mvmvif->bf_data.bf_enabled = true;

	return ret;
}
