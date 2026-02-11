iwl_mvm_rm_sta_common(struct iwl_mvm *mvm, u8 sta_id)
{
	struct ieee80211_sta *sta;
	struct iwl_mvm_rm_sta_cmd rm_sta_cmd = {
		.sta_id = sta_id,
	};
	int ret;

	sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));


	if (!sta) {
		IWL_ERR(mvm, "Invalid station id\n");
		return -EINVAL;
	}

	ret = iwl_mvm_send_cmd_pdu(mvm, REMOVE_STA, 0,
				   sizeof(rm_sta_cmd), &rm_sta_cmd);
	if (ret) {
		IWL_ERR(mvm, "Failed to remove station. Id=%d\n", sta_id);
		return ret;
	}

	return 0;
}
