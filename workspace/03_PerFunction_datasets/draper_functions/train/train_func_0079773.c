ocfs2_split_extent(handle_t *handle,
		       struct ocfs2_extent_tree *et,
		       struct ocfs2_path *path,
		       int split_index,
		       struct ocfs2_extent_rec *split_rec,
		       struct ocfs2_alloc_context *meta_ac,
		       struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret = 0;
	struct ocfs2_extent_list *el = path_leaf_el(path);
	struct buffer_head *last_eb_bh = NULL;
	struct ocfs2_extent_rec *rec = &el->l_recs[split_index];
	struct ocfs2_merge_ctxt ctxt;
	struct ocfs2_extent_list *rightmost_el;

	if (le32_to_cpu(rec->e_cpos) > le32_to_cpu(split_rec->e_cpos) ||
	    ((le32_to_cpu(rec->e_cpos) + le16_to_cpu(rec->e_leaf_clusters)) <
	     (le32_to_cpu(split_rec->e_cpos) + le16_to_cpu(split_rec->e_leaf_clusters)))) {
		ret = -EIO;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_figure_merge_contig_type(et, path, el,
					     split_index,
					     split_rec,
					     &ctxt);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}


	if (path->p_tree_depth) {
		struct ocfs2_extent_block *eb;

		ret = ocfs2_read_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &last_eb_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		eb = (struct ocfs2_extent_block *) last_eb_bh->b_data;
		rightmost_el = &eb->h_list;
	} else
		rightmost_el = path_root_el(path);

	if (rec->e_cpos == split_rec->e_cpos &&
	    rec->e_leaf_clusters == split_rec->e_leaf_clusters)
		ctxt.c_split_covers_rec = 1;
	else
		ctxt.c_split_covers_rec = 0;

	ctxt.c_has_empty_extent = ocfs2_is_empty_extent(&el->l_recs[0]);

	trace_ocfs2_split_extent(split_index, ctxt.c_contig_type,
				 ctxt.c_has_empty_extent,
				 ctxt.c_split_covers_rec);

	if (ctxt.c_contig_type == CONTIG_NONE) {
		if (ctxt.c_split_covers_rec)
			ret = ocfs2_replace_extent_rec(handle, et, path, el,
						       split_index, split_rec);
		else
			ret = ocfs2_split_and_insert(handle, et, path,
						     &last_eb_bh, split_index,
						     split_rec, meta_ac);
		if (ret)
			mlog_errno(ret);
	} else {
		ret = ocfs2_try_to_merge_extent(handle, et, path,
						split_index, split_rec,
						dealloc, &ctxt);
		if (ret)
			mlog_errno(ret);
	}

out:
	brelse(last_eb_bh);
	return ret;
}
