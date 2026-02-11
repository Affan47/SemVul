ft_sess_delete_all(struct ft_tport *tport)
{
	struct hlist_head *head;
	struct ft_sess *sess;

	for (head = tport->hash;
	     head < &tport->hash[FT_SESS_HASH_SIZE]; head++) {
		hlist_for_each_entry_rcu(sess, head, hash) {
			ft_sess_unhash(sess);
			transport_deregister_session_configfs(sess->se_sess);
			ft_sess_put(sess);
		}
	}
}
