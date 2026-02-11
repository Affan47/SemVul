ocfs2_dlm_next_res(struct ocfs2_lock_res *start,
						 struct ocfs2_dlm_seq_priv *priv)
{
	struct ocfs2_lock_res *iter, *ret = NULL;
	struct ocfs2_dlm_debug *dlm_debug = priv->p_dlm_debug;

	assert_spin_locked(&ocfs2_dlm_tracking_lock);

	list_for_each_entry(iter, &start->l_debug_list, l_debug_list) {

		if (&iter->l_debug_list == &dlm_debug->d_lockres_tracking) {
			mlog(0, "End of list found, %p\n", ret);
			break;
		}


		if (iter->l_ops != NULL) {
			ret = iter;
			break;
		}
	}

	return ret;
}
