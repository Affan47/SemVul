ocfs2_get_lockres_osb(struct ocfs2_lock_res *lockres)
{
	if (lockres->l_ops->get_osb)
		return lockres->l_ops->get_osb(lockres);

	return (struct ocfs2_super *)lockres->l_priv;
}
