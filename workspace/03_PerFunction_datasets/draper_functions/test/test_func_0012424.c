__ocfs2_find_path(struct ocfs2_caching_info *ci,
			     struct ocfs2_extent_list *root_el, u32 cpos,
			     path_insert_t *func, void *data)
{
	int i, ret = 0;
	u32 range;
	u64 blkno;
	struct buffer_head *bh = NULL;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;

	el = root_el;
	while (el->l_tree_depth) {
		if (le16_to_cpu(el->l_next_free_rec) == 0) {
			ocfs2_error(ocfs2_metadata_cache_get_super(ci),
				    "Owner %llu has empty extent list at depth %u\n",
				    (unsigned long long)ocfs2_metadata_cache_owner(ci),
				    le16_to_cpu(el->l_tree_depth));
			ret = -EROFS;
			goto out;

		}

		for(i = 0; i < le16_to_cpu(el->l_next_free_rec) - 1; i++) {
			rec = &el->l_recs[i];


			range = le32_to_cpu(rec->e_cpos) +
				ocfs2_rec_clusters(el, rec);
			if (cpos >= le32_to_cpu(rec->e_cpos) && cpos < range)
			    break;
		}

		blkno = le64_to_cpu(el->l_recs[i].e_blkno);
		if (blkno == 0) {
			ocfs2_error(ocfs2_metadata_cache_get_super(ci),
				    "Owner %llu has bad blkno in extent list at depth %u (index %d)\n",
				    (unsigned long long)ocfs2_metadata_cache_owner(ci),
				    le16_to_cpu(el->l_tree_depth), i);
			ret = -EROFS;
			goto out;
		}

		brelse(bh);
		bh = NULL;
		ret = ocfs2_read_extent_block(ci, blkno, &bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		eb = (struct ocfs2_extent_block *) bh->b_data;
		el = &eb->h_list;

		if (le16_to_cpu(el->l_next_free_rec) >
		    le16_to_cpu(el->l_count)) {
			ocfs2_error(ocfs2_metadata_cache_get_super(ci),
				    "Owner %llu has bad count in extent list at block %llu (next free=%u, count=%u)\n",
				    (unsigned long long)ocfs2_metadata_cache_owner(ci),
				    (unsigned long long)bh->b_blocknr,
				    le16_to_cpu(el->l_next_free_rec),
				    le16_to_cpu(el->l_count));
			ret = -EROFS;
			goto out;
		}

		if (func)
			func(data, bh);
	}

out:


	brelse(bh);

	return ret;
}
