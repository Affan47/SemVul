iscsit_tmr_abort_task(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	struct iscsi_cmd *ref_cmd;
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_tmr_req *tmr_req = cmd->tmr_req;
	struct se_tmr_req *se_tmr = cmd->se_cmd.se_tmr_req;
	struct iscsi_tm *hdr = (struct iscsi_tm *) buf;

	ref_cmd = iscsit_find_cmd_from_itt(conn, hdr->rtt);
	if (!ref_cmd) {
		pr_err("Unable to locate RefTaskTag: 0x%08x on CID:"
			" %hu.\n", hdr->rtt, conn->cid);
		return (iscsi_sna_gte(be32_to_cpu(hdr->refcmdsn), conn->sess->exp_cmd_sn) &&
			iscsi_sna_lte(be32_to_cpu(hdr->refcmdsn), (u32) atomic_read(&conn->sess->max_cmd_sn))) ?
			ISCSI_TMF_RSP_COMPLETE : ISCSI_TMF_RSP_NO_TASK;
	}
	if (ref_cmd->cmd_sn != be32_to_cpu(hdr->refcmdsn)) {
		pr_err("RefCmdSN 0x%08x does not equal"
			" task's CmdSN 0x%08x. Rejecting ABORT_TASK.\n",
			hdr->refcmdsn, ref_cmd->cmd_sn);
		return ISCSI_TMF_RSP_REJECTED;
	}

	se_tmr->ref_task_tag		= (__force u32)hdr->rtt;
	tmr_req->ref_cmd		= ref_cmd;
	tmr_req->exp_data_sn		= be32_to_cpu(hdr->exp_datasn);

	return ISCSI_TMF_RSP_COMPLETE;
}
