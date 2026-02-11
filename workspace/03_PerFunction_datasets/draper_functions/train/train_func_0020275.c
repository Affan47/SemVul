sbp_session_find_by_guid(
	struct sbp_tpg *tpg, u64 guid)
{
	struct se_session *se_sess;
	struct sbp_session *sess, *found = NULL;

	spin_lock_bh(&tpg->se_tpg.session_lock);
	list_for_each_entry(se_sess, &tpg->se_tpg.tpg_sess_list, sess_list) {
		sess = se_sess->fabric_sess_ptr;
		if (sess->guid == guid)
			found = sess;
	}
	spin_unlock_bh(&tpg->se_tpg.session_lock);

	return found;
}
