iwl_mvm_tt_tx_protection(struct iwl_mvm *mvm, bool enable)
{
	struct ieee80211_sta *sta;
	struct iwl_mvm_sta *mvmsta;
	int i, err;

	for (i = 0; i < IWL_MVM_STATION_COUNT; i++) {
		sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		if (IS_ERR_OR_NULL(sta))
			continue;
		mvmsta = iwl_mvm_sta_from_mac80211(sta);
		if (enable == mvmsta->tt_tx_protection)
			continue;
		err = iwl_mvm_tx_protection(mvm, mvmsta, enable);
		if (err) {
			IWL_ERR(mvm, "Failed to %s Tx protection\n",
				enable ? "enable" : "disable");
		} else {
			IWL_DEBUG_TEMP(mvm, "%s Tx protection\n",
				       enable ? "Enable" : "Disable");
			mvmsta->tt_tx_protection = enable;
		}
	}
}
