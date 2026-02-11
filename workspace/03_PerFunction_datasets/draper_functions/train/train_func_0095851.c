iwl_mvm_te_check_disconnect(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif,
					const char *errmsg)
{
	if (vif->type != NL80211_IFTYPE_STATION)
		return false;
	if (vif->bss_conf.assoc && vif->bss_conf.dtim_period)
		return false;
	if (errmsg)
		IWL_ERR(mvm, "%s\n", errmsg);

	iwl_mvm_connection_loss(mvm, vif, errmsg);
	return true;
}
