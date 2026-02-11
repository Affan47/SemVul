ocfs2_insert_path(handle_t *handle,
			     struct ocfs2_extent_tree *et,
			     struct ocfs2_path *left_path,
			     struct ocfs2_path *right_path,
			     struct ocfs2_extent_rec *insert_rec,
			     struct ocfs2_insert_type *insert)
{
	int ret, subtree_index;
	struct buffer_head *leaf_bh = path_leaf_bh(right_path);

	if (left_path) {


		ret = ocfs2_extend_trans(handle, left_path->p_tree_depth);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_journal_access_path(et->et_ci, handle, left_path);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
	}


	ret = ocfs2_journal_access_path(et->et_ci, handle, right_path);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	if (insert->ins_split != SPLIT_NONE) {


		ocfs2_split_record(et, left_path, right_path,
				   insert_rec, insert->ins_split);


		if (left_path)
			ocfs2_journal_dirty(handle,
					    path_leaf_bh(left_path));
	} else
		ocfs2_insert_at_leaf(et, insert_rec, path_leaf_el(right_path),
				     insert);

	ocfs2_journal_dirty(handle, leaf_bh);

	if (left_path) {


		subtree_index = ocfs2_find_subtree_root(et, left_path,
							right_path);
		ocfs2_complete_edge_insert(handle, left_path, right_path,
					   subtree_index);
	}

	ret = 0;
out:
	return ret;
}
