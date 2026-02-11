iscsit_setup_nop_out(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
			 struct iscsi_nopout *hdr)
{
	u32 payload_length = ntoh24(hdr->dlength);

	if (!(hdr->flags & ISCSI_FLAG_CMD_FINAL)) {
		pr_err("NopOUT Flag's, Left Most Bit not set, protocol error.\n");
		if (!cmd)
			return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						 (unsigned char *)hdr);

		return iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (unsigned char *)hdr);
	}

	if (hdr->itt == RESERVED_ITT && !(hdr->opcode & ISCSI_OP_IMMEDIATE)) {
		pr_err("NOPOUT ITT is reserved, but Immediate Bit is"
			" not set, protocol error.\n");
		if (!cmd)
			return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						 (unsigned char *)hdr);

		return iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (unsigned char *)hdr);
	}

	if (payload_length > conn->conn_ops->MaxXmitDataSegmentLength) {
		pr_err("NOPOUT Ping Data DataSegmentLength: %u is"
			" greater than MaxXmitDataSegmentLength: %u, protocol"
			" error.\n", payload_length,
			conn->conn_ops->MaxXmitDataSegmentLength);
		if (!cmd)
			return iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						 (unsigned char *)hdr);

		return iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (unsigned char *)hdr);
	}

	pr_debug("Got NOPOUT Ping %s ITT: 0x%08x, TTT: 0x%08x,"
		" CmdSN: 0x%08x, ExpStatSN: 0x%08x, Length: %u\n",
		hdr->itt == RESERVED_ITT ? "Response" : "Request",
		hdr->itt, hdr->ttt, hdr->cmdsn, hdr->exp_statsn,
		payload_length);


	if (hdr->ttt == cpu_to_be32(0xFFFFFFFF)) {
		cmd->iscsi_opcode	= ISCSI_OP_NOOP_OUT;
		cmd->i_state		= ISTATE_SEND_NOPIN;
		cmd->immediate_cmd	= ((hdr->opcode & ISCSI_OP_IMMEDIATE) ?
						1 : 0);
		conn->sess->init_task_tag = cmd->init_task_tag = hdr->itt;
		cmd->targ_xfer_tag	= 0xFFFFFFFF;
		cmd->cmd_sn		= be32_to_cpu(hdr->cmdsn);
		cmd->exp_stat_sn	= be32_to_cpu(hdr->exp_statsn);
		cmd->data_direction	= DMA_NONE;
	}

	return 0;
}
