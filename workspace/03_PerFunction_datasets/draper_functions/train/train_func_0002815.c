iscsi_conn_failure(struct iscsi_conn *conn, enum iscsi_err err)
{
	struct iscsi_session *session = conn->session;

	spin_lock_bh(&session->lock);
	if (session->state == ISCSI_STATE_FAILED) {
		spin_unlock_bh(&session->lock);
		return;
	}

	if (conn->stop_stage == 0)
		session->state = ISCSI_STATE_FAILED;
	spin_unlock_bh(&session->lock);

	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx);
	iscsi_conn_error_event(conn->cls_conn, err);
}
