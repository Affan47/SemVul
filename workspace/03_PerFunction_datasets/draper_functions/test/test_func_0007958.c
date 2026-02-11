ocfs2_adjust_refcount_rec(handle_t *handle,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *ref_root_bh,
				     struct buffer_head *ref_leaf_bh,
				     struct ocfs2_refcount_rec *rec)
{
	int ret = 0, i;
	u32 new_cpos, old_cpos;
	struct ocfs2_path *path = NULL;
	struct ocfs2_extent_tree et;
	struct ocfs2_refcount_block *rb =
		(struct ocfs2_refcount_block *)ref_root_bh->b_data;
	struct ocfs2_extent_list *el;

	if (!(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL))
		goto out;

	rb = (struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	old_cpos = le32_to_cpu(rb->rf_cpos);
	new_cpos = le64_to_cpu(rec->r_cpos) & OCFS2_32BIT_POS_MASK;
	if (old_cpos <= new_cpos)
		goto out;

	ocfs2_init_refcount_extent_tree(&et, ci, ref_root_bh);

	path = ocfs2_new_path_from_et(&et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_path(ci, path, old_cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}


	ret = ocfs2_extend_trans(handle, 2);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_eb(handle, ci, path_leaf_bh(path),
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}


	el = path_leaf_el(path);

	for (i = 0; i < le16_to_cpu(el->l_next_free_rec); i++)
		if (le32_to_cpu(el->l_recs[i].e_cpos) == old_cpos)
			break;

	BUG_ON(i == le16_to_cpu(el->l_next_free_rec));

	el->l_recs[i].e_cpos = cpu_to_le32(new_cpos);


	rb->rf_cpos = cpu_to_le32(new_cpos);

	ocfs2_journal_dirty(handle, path_leaf_bh(path));
	ocfs2_journal_dirty(handle, ref_leaf_bh);

out:
	ocfs2_free_path(path);
	return ret;
}
