iwl_mvm_tof_config_cmd(struct iwl_mvm *mvm)
{
	struct iwl_tof_config_cmd *cmd = &mvm->tof_data.tof_cfg;
	bool enabled;

	lockdep_assert_held(&mvm->mutex);

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT))
		return -EINVAL;

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_tof_iterator, &enabled);
	if (!enabled) {
		IWL_DEBUG_INFO(mvm, "ToF is not supported (non bss vif)\n");
		return -EINVAL;
	}

	mvm->tof_data.active_range_request = IWL_MVM_TOF_RANGE_REQ_MAX_ID;
	return iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(TOF_CMD,
						    IWL_ALWAYS_LONG_GROUP, 0),
				    0, sizeof(*cmd), cmd);
}
