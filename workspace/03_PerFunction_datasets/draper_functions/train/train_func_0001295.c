ocfs2_prepare_downconvert(struct ocfs2_lock_res *lockres,
					      int new_level)
{
	assert_spin_locked(&lockres->l_lock);

	BUG_ON(lockres->l_blocking <= DLM_LOCK_NL);

	if (lockres->l_level <= new_level) {
		mlog(ML_ERROR, "lockres %s, lvl %d <= %d, blcklst %d, mask %d, "
		     "type %d, flags 0x%lx, hold %d %d, act %d %d, req %d, "
		     "block %d, pgen %d\n", lockres->l_name, lockres->l_level,
		     new_level, list_empty(&lockres->l_blocked_list),
		     list_empty(&lockres->l_mask_waiters), lockres->l_type,
		     lockres->l_flags, lockres->l_ro_holders,
		     lockres->l_ex_holders, lockres->l_action,
		     lockres->l_unlock_action, lockres->l_requested,
		     lockres->l_blocking, lockres->l_pending_gen);
		BUG();
	}

	mlog(ML_BASTS, "lockres %s, level %d => %d, blocking %d\n",
	     lockres->l_name, lockres->l_level, new_level, lockres->l_blocking);

	lockres->l_action = OCFS2_AST_DOWNCONVERT;
	lockres->l_requested = new_level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	return lockres_set_pending(lockres);
}
