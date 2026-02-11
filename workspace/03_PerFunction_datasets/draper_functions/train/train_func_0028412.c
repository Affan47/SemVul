iscsit_task_reassign_remove_cmd(
	struct iscsi_cmd *cmd,
	struct iscsi_conn_recovery *cr,
	struct iscsi_session *sess)
{
	int ret;

	spin_lock(&cr->conn_recovery_cmd_lock);
	ret = iscsit_remove_cmd_from_connection_recovery(cmd, sess);
	spin_unlock(&cr->conn_recovery_cmd_lock);
	if (!ret) {
		pr_debug("iSCSI connection recovery successful for CID:"
			" %hu on SID: %u\n", cr->cid, sess->sid);
		iscsit_remove_active_connection_recovery_entry(cr, sess);
	}
}
