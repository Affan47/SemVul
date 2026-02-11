iwl_mvm_update_mcc(struct iwl_mvm *mvm, const char *alpha2,
		   enum iwl_mcc_source src_id)
{
	struct iwl_mcc_update_cmd mcc_update_cmd = {
		.mcc = cpu_to_le16(alpha2[0] << 8 | alpha2[1]),
		.source_id = (u8)src_id,
	};
	struct iwl_mcc_update_resp *mcc_resp, *resp_cp = NULL;
	struct iwl_rx_packet *pkt;
	struct iwl_host_cmd cmd = {
		.id = MCC_UPDATE_CMD,
		.flags = CMD_WANT_SKB,
		.data = { &mcc_update_cmd },
	};

	int ret;
	u32 status;
	int resp_len, n_channels;
	u16 mcc;

	if (WARN_ON_ONCE(!iwl_mvm_is_lar_supported(mvm)))
		return ERR_PTR(-EOPNOTSUPP);

	cmd.len[0] = sizeof(struct iwl_mcc_update_cmd);

	IWL_DEBUG_LAR(mvm, "send MCC update to FW with '%c%c' src = %d\n",
		      alpha2[0], alpha2[1], src_id);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (ret)
		return ERR_PTR(ret);

	pkt = cmd.resp_pkt;


	mcc_resp = (void *)pkt->data;
	status = le32_to_cpu(mcc_resp->status);

	mcc = le16_to_cpu(mcc_resp->mcc);


	if (mcc == 0) {
		mcc = 0x3030;
		mcc_resp->mcc = cpu_to_le16(mcc);
	}

	n_channels =  __le32_to_cpu(mcc_resp->n_channels);
	IWL_DEBUG_LAR(mvm,
		      "MCC response status: 0x%x. new MCC: 0x%x ('%c%c') change: %d n_chans: %d\n",
		      status, mcc, mcc >> 8, mcc & 0xff,
		      !!(status == MCC_RESP_NEW_CHAN_PROFILE), n_channels);

	resp_len = sizeof(*mcc_resp) + n_channels * sizeof(__le32);
	resp_cp = kmemdup(mcc_resp, resp_len, GFP_KERNEL);
	if (!resp_cp) {
		ret = -ENOMEM;
		goto exit;
	}

	ret = 0;
exit:
	iwl_free_resp(&cmd);
	if (ret)
		return ERR_PTR(ret);
	return resp_cp;
}
