iwl_send_scan_abort(struct iwl_priv *priv)
{
	int ret;
	struct iwl_host_cmd cmd = {
		.id = REPLY_SCAN_ABORT_CMD,
		.flags = CMD_WANT_SKB,
	};
	__le32 *status;


	if (!test_bit(STATUS_READY, &priv->status) ||
	    !test_bit(STATUS_SCAN_HW, &priv->status) ||
	    test_bit(STATUS_FW_ERROR, &priv->status))
		return -EIO;

	ret = iwl_dvm_send_cmd(priv, &cmd);
	if (ret)
		return ret;

	status = (void *)cmd.resp_pkt->data;
	if (*status != CAN_ABORT_STATUS) {


		IWL_DEBUG_SCAN(priv, "SCAN_ABORT ret %d.\n",
			       le32_to_cpu(*status));
		ret = -EIO;
	}

	iwl_free_resp(&cmd);
	return ret;
}
