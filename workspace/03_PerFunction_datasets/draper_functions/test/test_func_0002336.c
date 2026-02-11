iwl_mvm_tof_range_request_cmd(struct iwl_mvm *mvm,
				  struct ieee80211_vif *vif)
{
	struct iwl_host_cmd cmd = {
		.id = iwl_cmd_id(TOF_CMD, IWL_ALWAYS_LONG_GROUP, 0),
		.len = { sizeof(mvm->tof_data.range_req), },

		.dataflags = { IWL_HCMD_DFL_NOCOPY, },
	};

	lockdep_assert_held(&mvm->mutex);

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT))
		return -EINVAL;

	if (ieee80211_vif_type_p2p(vif) !=  NL80211_IFTYPE_STATION) {
		IWL_ERR(mvm, "Cannot send range request, not STA mode\n");
		return -EIO;
	}


	if (mvm->tof_data.active_range_request !=
		IWL_MVM_TOF_RANGE_REQ_MAX_ID) {
		IWL_ERR(mvm, "Cannot send range req, already active req %d\n",
			mvm->tof_data.active_range_request);
		return -EIO;
	}

	mvm->tof_data.active_range_request = mvm->tof_data.range_req.request_id;

	cmd.data[0] = &mvm->tof_data.range_req;
	return iwl_mvm_send_cmd(mvm, &cmd);
}
