ocfs2_inc_holders(struct ocfs2_lock_res *lockres,
				     int level)
{
	BUG_ON(!lockres);

	switch(level) {
	case DLM_LOCK_EX:
		lockres->l_ex_holders++;
		break;
	case DLM_LOCK_PR:
		lockres->l_ro_holders++;
		break;
	default:
		BUG();
	}
}
