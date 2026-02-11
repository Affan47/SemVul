iscsit_attach_inactive_connection_recovery_entry(
	struct iscsi_session *sess,
	struct iscsi_conn_recovery *cr)
{
	spin_lock(&sess->cr_i_lock);
	list_add_tail(&cr->cr_list, &sess->cr_inactive_list);

	sess->conn_recovery_count++;
	pr_debug("Incremented connection recovery count to %u for"
		" SID: %u\n", sess->conn_recovery_count, sess->sid);
	spin_unlock(&sess->cr_i_lock);

	return 0;
}
