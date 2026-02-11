iscsit_find_cmd_from_itt_or_dump(
	struct iscsi_conn *conn,
	itt_t init_task_tag,
	u32 length)
{
	struct iscsi_cmd *cmd;

	spin_lock_bh(&conn->cmd_lock);
	list_for_each_entry(cmd, &conn->conn_cmd_list, i_conn_node) {
		if (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT)
			continue;
		if (cmd->init_task_tag == init_task_tag) {
			spin_unlock_bh(&conn->cmd_lock);
			return cmd;
		}
	}
	spin_unlock_bh(&conn->cmd_lock);

	pr_err("Unable to locate ITT: 0x%08x on CID: %hu,"
			" dumping payload\n", init_task_tag, conn->cid);
	if (length)
		iscsit_dump_data_payload(conn, length, 1);

	return NULL;
}
