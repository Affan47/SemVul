ocfs2_lock_res_free(struct ocfs2_lock_res *res)
{
	if (!(res->l_flags & OCFS2_LOCK_INITIALIZED))
		return;

	ocfs2_remove_lockres_tracking(res);

	mlog_bug_on_msg(!list_empty(&res->l_blocked_list),
			"Lockres %s is on the blocked list\n",
			res->l_name);
	mlog_bug_on_msg(!list_empty(&res->l_mask_waiters),
			"Lockres %s has mask waiters pending\n",
			res->l_name);
	mlog_bug_on_msg(spin_is_locked(&res->l_lock),
			"Lockres %s is locked\n",
			res->l_name);
	mlog_bug_on_msg(res->l_ro_holders,
			"Lockres %s has %u ro holders\n",
			res->l_name, res->l_ro_holders);
	mlog_bug_on_msg(res->l_ex_holders,
			"Lockres %s has %u ex holders\n",
			res->l_name, res->l_ex_holders);


	memset(&res->l_lksb, 0, sizeof(res->l_lksb));

	res->l_flags = 0UL;
}
