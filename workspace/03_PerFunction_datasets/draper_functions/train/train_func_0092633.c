ocfs2_dlm_unlock(struct ocfs2_cluster_connection *conn,
		     struct ocfs2_dlm_lksb *lksb,
		     u32 flags)
{
	BUG_ON(lksb->lksb_conn == NULL);

	return active_stack->sp_ops->dlm_unlock(conn, lksb, flags);
}
