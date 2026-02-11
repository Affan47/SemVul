discard_next_dnode(struct f2fs_sb_info *sbi, block_t blkaddr)
{
	int err = -ENOTSUPP;

	if (test_opt(sbi, DISCARD)) {
		struct seg_entry *se = get_seg_entry(sbi,
				GET_SEGNO(sbi, blkaddr));
		unsigned int offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);

		if (f2fs_test_bit(offset, se->discard_map))
			return false;

		err = f2fs_issue_discard(sbi, blkaddr, 1);
	}

	if (err) {
		update_meta_page(sbi, NULL, blkaddr);
		return true;
	}
	return false;
}
