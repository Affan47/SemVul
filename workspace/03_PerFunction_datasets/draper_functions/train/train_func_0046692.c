ocfs2_extend_xattr_bucket(struct inode *inode,
				     handle_t *handle,
				     struct ocfs2_xattr_bucket *first,
				     u64 target_blk,
				     u32 num_clusters)
{
	int ret, credits;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u16 blk_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	u64 end_blk;
	u16 new_bucket = le16_to_cpu(bucket_xh(first)->xh_num_buckets);

	trace_ocfs2_extend_xattr_bucket((unsigned long long)target_blk,
					(unsigned long long)bucket_blkno(first),
					num_clusters, new_bucket);


	BUG_ON(new_bucket >=
	       (num_clusters * ocfs2_xattr_buckets_per_cluster(osb)));


	end_blk = bucket_blkno(first) + ((new_bucket - 1) * blk_per_bucket);


	credits = (end_blk - target_blk) + (3 * blk_per_bucket);
	ret = ocfs2_extend_trans(handle, credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_xattr_bucket_journal_access(handle, first,
						OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	while (end_blk != target_blk) {
		ret = ocfs2_cp_xattr_bucket(inode, handle, end_blk,
					    end_blk + blk_per_bucket, 0);
		if (ret)
			goto out;
		end_blk -= blk_per_bucket;
	}


	ret = ocfs2_divide_xattr_bucket(inode, handle, target_blk,
					target_blk + blk_per_bucket, NULL, 0);

	le16_add_cpu(&bucket_xh(first)->xh_num_buckets, 1);
	ocfs2_xattr_bucket_journal_dirty(handle, first);

out:
	return ret;
}
