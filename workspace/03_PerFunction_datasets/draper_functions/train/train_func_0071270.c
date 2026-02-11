iwl_mvm_bt_coex_is_mimo_allowed_old(struct iwl_mvm *mvm,
					 struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	enum iwl_bt_coex_lut_type lut_type;

	if (mvm->last_bt_notif_old.ttc_enabled)
		return true;

	if (le32_to_cpu(mvm->last_bt_notif_old.bt_activity_grading) <
	    BT_HIGH_TRAFFIC)
		return true;


	lut_type = iwl_get_coex_type(mvm, mvmsta->vif);
	return lut_type != BT_COEX_LOOSE_LUT;
}
