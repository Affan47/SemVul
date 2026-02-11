ocfs2_validate_gd_self(struct super_block *sb,
				  struct buffer_head *bh,
				  int resize)
{
	struct ocfs2_group_desc *gd = (struct ocfs2_group_desc *)bh->b_data;

	if (!OCFS2_IS_VALID_GROUP_DESC(gd)) {
		do_error("Group descriptor #%llu has bad signature %.*s\n",
			 (unsigned long long)bh->b_blocknr, 7,
			 gd->bg_signature);
	}

	if (le64_to_cpu(gd->bg_blkno) != bh->b_blocknr) {
		do_error("Group descriptor #%llu has an invalid bg_blkno of %llu\n",
			 (unsigned long long)bh->b_blocknr,
			 (unsigned long long)le64_to_cpu(gd->bg_blkno));
	}

	if (le32_to_cpu(gd->bg_generation) != OCFS2_SB(sb)->fs_generation) {
		do_error("Group descriptor #%llu has an invalid fs_generation of #%u\n",
			 (unsigned long long)bh->b_blocknr,
			 le32_to_cpu(gd->bg_generation));
	}

	if (le16_to_cpu(gd->bg_free_bits_count) > le16_to_cpu(gd->bg_bits)) {
		do_error("Group descriptor #%llu has bit count %u but claims that %u are free\n",
			 (unsigned long long)bh->b_blocknr,
			 le16_to_cpu(gd->bg_bits),
			 le16_to_cpu(gd->bg_free_bits_count));
	}

	if (le16_to_cpu(gd->bg_bits) > (8 * le16_to_cpu(gd->bg_size))) {
		do_error("Group descriptor #%llu has bit count %u but max bitmap bits of %u\n",
			 (unsigned long long)bh->b_blocknr,
			 le16_to_cpu(gd->bg_bits),
			 8 * le16_to_cpu(gd->bg_size));
	}

	return 0;
}
