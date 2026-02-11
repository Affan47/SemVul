iscsit_build_reject(struct iscsi_cmd *cmd, struct iscsi_conn *conn,
		    struct iscsi_reject *hdr)
{
	hdr->opcode		= ISCSI_OP_REJECT;
	hdr->reason		= cmd->reject_reason;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	hton24(hdr->dlength, ISCSI_HDR_LEN);
	hdr->ffffffff		= cpu_to_be32(0xffffffff);
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));

}
