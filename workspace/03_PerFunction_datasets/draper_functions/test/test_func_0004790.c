ocfs2_verify_volume(struct ocfs2_dinode *di,
			       struct buffer_head *bh,
			       u32 blksz,
			       struct ocfs2_blockcheck_stats *stats)
{
	int status = -EAGAIN;

	if (memcmp(di->i_signature, OCFS2_SUPER_BLOCK_SIGNATURE,
		   strlen(OCFS2_SUPER_BLOCK_SIGNATURE)) == 0) {

		if (le32_to_cpu(di->id2.i_super.s_feature_incompat) &
		    OCFS2_FEATURE_INCOMPAT_META_ECC) {
			status = ocfs2_block_check_validate(bh->b_data,
							    bh->b_size,
							    &di->i_check,
							    stats);
			if (status)
				goto out;
		}
		status = -EINVAL;
		if ((1 << le32_to_cpu(di->id2.i_super.s_blocksize_bits)) != blksz) {
			mlog(ML_ERROR, "found superblock with incorrect block "
			     "size: found %u, should be %u\n",
			     1 << le32_to_cpu(di->id2.i_super.s_blocksize_bits),
			       blksz);
		} else if (le16_to_cpu(di->id2.i_super.s_major_rev_level) !=
			   OCFS2_MAJOR_REV_LEVEL ||
			   le16_to_cpu(di->id2.i_super.s_minor_rev_level) !=
			   OCFS2_MINOR_REV_LEVEL) {
			mlog(ML_ERROR, "found superblock with bad version: "
			     "found %u.%u, should be %u.%u\n",
			     le16_to_cpu(di->id2.i_super.s_major_rev_level),
			     le16_to_cpu(di->id2.i_super.s_minor_rev_level),
			     OCFS2_MAJOR_REV_LEVEL,
			     OCFS2_MINOR_REV_LEVEL);
		} else if (bh->b_blocknr != le64_to_cpu(di->i_blkno)) {
			mlog(ML_ERROR, "bad block number on superblock: "
			     "found %llu, should be %llu\n",
			     (unsigned long long)le64_to_cpu(di->i_blkno),
			     (unsigned long long)bh->b_blocknr);
		} else if (le32_to_cpu(di->id2.i_super.s_clustersize_bits) < 12 ||
			    le32_to_cpu(di->id2.i_super.s_clustersize_bits) > 20) {
			mlog(ML_ERROR, "bad cluster size found: %u\n",
			     1 << le32_to_cpu(di->id2.i_super.s_clustersize_bits));
		} else if (!le64_to_cpu(di->id2.i_super.s_root_blkno)) {
			mlog(ML_ERROR, "bad root_blkno: 0\n");
		} else if (!le64_to_cpu(di->id2.i_super.s_system_dir_blkno)) {
			mlog(ML_ERROR, "bad system_dir_blkno: 0\n");
		} else if (le16_to_cpu(di->id2.i_super.s_max_slots) > OCFS2_MAX_SLOTS) {
			mlog(ML_ERROR,
			     "Superblock slots found greater than file system "
			     "maximum: found %u, max %u\n",
			     le16_to_cpu(di->id2.i_super.s_max_slots),
			     OCFS2_MAX_SLOTS);
		} else {

			status = 0;
		}
	}

out:
	if (status && status != -EAGAIN)
		mlog_errno(status);
	return status;
}
