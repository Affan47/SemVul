sbp_sense_mangle(struct sbp_target_request *req)
{
	struct se_cmd *se_cmd = &req->se_cmd;
	u8 *sense = req->sense_buf;
	u8 *status = req->status.data;

	WARN_ON(se_cmd->scsi_sense_length < 18);

	switch (sense[0] & 0x7f) {
	case 0x70:
		status[0] = 0 << 6;
		break;
	case 0x71:
		status[0] = 1 << 6;
		break;
	case 0x72:
	case 0x73:
	default:


		pr_err("sbp_send_sense: unknown sense format: 0x%x\n",
			sense[0]);
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQUEST_ABORTED));
		return;
	}

	status[0] |= se_cmd->scsi_status & 0x3f;
	status[1] =
		(sense[0] & 0x80) |
		((sense[2] & 0xe0) >> 1) |
		(sense[2] & 0x0f);
	status[2] = se_cmd->scsi_asc;
	status[3] = se_cmd->scsi_ascq;


	status[4] = sense[3];
	status[5] = sense[4];
	status[6] = sense[5];
	status[7] = sense[6];


	status[8] = sense[8];
	status[9] = sense[9];
	status[10] = sense[10];
	status[11] = sense[11];


	status[12] = sense[14];


	status[13] = sense[15];
	status[14] = sense[16];
	status[15] = sense[17];

	req->status.status |= cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_DEAD(0) |
		STATUS_BLOCK_LEN(5) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
}
