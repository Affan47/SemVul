sbp_write_pending(struct se_cmd *se_cmd)
{
	struct sbp_target_request *req = container_of(se_cmd,
			struct sbp_target_request, se_cmd);
	int ret;

	ret = sbp_rw_data(req);
	if (ret) {
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(
				STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(
				SBP_STATUS_UNSPECIFIED_ERROR));
		sbp_send_status(req);
		return ret;
	}

	target_execute_cmd(se_cmd);
	return 0;
}
