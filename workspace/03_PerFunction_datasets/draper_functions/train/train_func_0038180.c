lio_tpg_shutdown_session(struct se_session *se_sess)
{
	struct iscsi_session *sess = se_sess->fabric_sess_ptr;
	struct se_portal_group *se_tpg = &sess->tpg->tpg_se_tpg;

	spin_lock_bh(&se_tpg->session_lock);
	spin_lock(&sess->conn_lock);
	if (atomic_read(&sess->session_fall_back_to_erl0) ||
	    atomic_read(&sess->session_logout) ||
	    (sess->time2retain_timer_flags & ISCSI_TF_EXPIRED)) {
		spin_unlock(&sess->conn_lock);
		spin_unlock_bh(&se_tpg->session_lock);
		return 0;
	}
	atomic_set(&sess->session_reinstatement, 1);
	atomic_set(&sess->session_fall_back_to_erl0, 1);
	spin_unlock(&sess->conn_lock);

	iscsit_stop_time2retain_timer(sess);
	spin_unlock_bh(&se_tpg->session_lock);

	iscsit_stop_session(sess, 1, 1);
	return 1;
}
