bnx2i_process_scsi_cmd_resp(struct iscsi_session *session,
				struct bnx2i_conn *bnx2i_conn,
				struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct bnx2i_hba *hba = bnx2i_conn->hba;
	struct bnx2i_cmd_response *resp_cqe;
	struct bnx2i_cmd *bnx2i_cmd;
	struct iscsi_task *task;
	struct iscsi_scsi_rsp *hdr;
	u32 datalen = 0;

	resp_cqe = (struct bnx2i_cmd_response *)cqe;
	spin_lock_bh(&session->lock);
	task = iscsi_itt_to_task(conn,
				 resp_cqe->itt & ISCSI_CMD_RESPONSE_INDEX);
	if (!task)
		goto fail;

	bnx2i_cmd = task->dd_data;

	if (bnx2i_cmd->req.op_attr & ISCSI_CMD_REQUEST_READ) {
		conn->datain_pdus_cnt +=
			resp_cqe->task_stat.read_stat.num_data_ins;
		conn->rxdata_octets +=
			bnx2i_cmd->req.total_data_transfer_length;
		ADD_STATS_64(hba, rx_pdus,
			     resp_cqe->task_stat.read_stat.num_data_ins);
		ADD_STATS_64(hba, rx_bytes,
			     bnx2i_cmd->req.total_data_transfer_length);
	} else {
		conn->dataout_pdus_cnt +=
			resp_cqe->task_stat.write_stat.num_data_outs;
		conn->r2t_pdus_cnt +=
			resp_cqe->task_stat.write_stat.num_r2ts;
		conn->txdata_octets +=
			bnx2i_cmd->req.total_data_transfer_length;
		ADD_STATS_64(hba, tx_pdus,
			     resp_cqe->task_stat.write_stat.num_data_outs);
		ADD_STATS_64(hba, tx_bytes,
			     bnx2i_cmd->req.total_data_transfer_length);
		ADD_STATS_64(hba, rx_pdus,
			     resp_cqe->task_stat.write_stat.num_r2ts);
	}
	bnx2i_iscsi_unmap_sg_list(bnx2i_cmd);

	hdr = (struct iscsi_scsi_rsp *)task->hdr;
	resp_cqe = (struct bnx2i_cmd_response *)cqe;
	hdr->opcode = resp_cqe->op_code;
	hdr->max_cmdsn = cpu_to_be32(resp_cqe->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(resp_cqe->exp_cmd_sn);
	hdr->response = resp_cqe->response;
	hdr->cmd_status = resp_cqe->status;
	hdr->flags = resp_cqe->response_flags;
	hdr->residual_count = cpu_to_be32(resp_cqe->residual_count);

	if (resp_cqe->op_code == ISCSI_OP_SCSI_DATA_IN)
		goto done;

	if (resp_cqe->status == SAM_STAT_CHECK_CONDITION) {
		datalen = resp_cqe->data_length;
		if (datalen < 2)
			goto done;

		if (datalen > BNX2I_RQ_WQE_SIZE) {
			iscsi_conn_printk(KERN_ERR, conn,
					  "sense data len %d > RQ sz\n",
					  datalen);
			datalen = BNX2I_RQ_WQE_SIZE;
		} else if (datalen > ISCSI_DEF_MAX_RECV_SEG_LEN) {
			iscsi_conn_printk(KERN_ERR, conn,
					  "sense data len %d > conn data\n",
					  datalen);
			datalen = ISCSI_DEF_MAX_RECV_SEG_LEN;
		}

		bnx2i_get_rq_buf(bnx2i_cmd->conn, conn->data, datalen);
		bnx2i_put_rq_buf(bnx2i_cmd->conn, 1);
	}

done:
	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)hdr,
			     conn->data, datalen);
fail:
	spin_unlock_bh(&session->lock);
	return 0;
}
