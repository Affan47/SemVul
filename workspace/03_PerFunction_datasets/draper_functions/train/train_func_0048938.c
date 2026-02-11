iscsit_build_task_mgt_rsp(struct iscsi_cmd *cmd, struct iscsi_conn *conn,
			  struct iscsi_tm_rsp *hdr)
{
	struct se_tmr_req *se_tmr = cmd->se_cmd.se_tmr_req;

	hdr->opcode		= ISCSI_OP_SCSI_TMFUNC_RSP;
	hdr->flags		= ISCSI_FLAG_CMD_FINAL;
	hdr->response		= iscsit_convert_tcm_tmr_rsp(se_tmr);
	hdr->itt		= cmd->init_task_tag;
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));

	pr_debug("Built Task Management Response ITT: 0x%08x,"
		" StatSN: 0x%08x, Response: 0x%02x, CID: %hu\n",
		cmd->init_task_tag, cmd->stat_sn, hdr->response, conn->cid);
}
