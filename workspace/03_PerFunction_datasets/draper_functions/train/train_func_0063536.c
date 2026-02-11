mvumi_inquiry(struct mvumi_hba *mhba,
	unsigned int id, struct mvumi_cmd *cmd)
{
	struct mvumi_msg_frame *frame;
	u64 wwid = 0;
	int cmd_alloc = 0;
	int data_buf_len = 64;

	if (!cmd) {
		cmd = mvumi_create_internal_cmd(mhba, data_buf_len);
		if (cmd)
			cmd_alloc = 1;
		else
			return 0;
	} else {
		memset(cmd->data_buf, 0, data_buf_len);
	}
	cmd->scmd = NULL;
	cmd->cmd_status = REQ_STATUS_PENDING;
	atomic_set(&cmd->sync_cmd, 0);
	frame = cmd->frame;
	frame->device_id = (u16) id;
	frame->cmd_flag = CMD_FLAG_DATA_IN;
	frame->req_function = CL_FUN_SCSI_CMD;
	frame->cdb_length = 6;
	frame->data_transfer_length = MVUMI_INQUIRY_LENGTH;
	memset(frame->cdb, 0, frame->cdb_length);
	frame->cdb[0] = INQUIRY;
	frame->cdb[4] = frame->data_transfer_length;

	mvumi_issue_blocked_cmd(mhba, cmd);

	if (cmd->cmd_status == SAM_STAT_GOOD) {
		if (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9143)
			wwid = id + 1;
		else
			memcpy((void *)&wwid,
			       (cmd->data_buf + MVUMI_INQUIRY_UUID_OFF),
			       MVUMI_INQUIRY_UUID_LEN);
		dev_dbg(&mhba->pdev->dev,
			"inquiry device(0:%d:0) wwid(%llx)\n", id, wwid);
	} else {
		wwid = 0;
	}
	if (cmd_alloc)
		mvumi_delete_internal_cmd(mhba, cmd);

	return wwid;
}
