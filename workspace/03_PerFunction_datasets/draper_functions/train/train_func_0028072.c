ext4_validate_block_bitmap(struct super_block *sb,
				      struct ext4_group_desc *desc,
				      ext4_group_t block_group,
				      struct buffer_head *bh)
{
	ext4_fsblk_t	blk;
	struct ext4_group_info *grp = ext4_get_group_info(sb, block_group);
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (buffer_verified(bh))
		return 0;
	if (EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
		return -EFSCORRUPTED;

	ext4_lock_group(sb, block_group);
	if (unlikely(!ext4_block_bitmap_csum_verify(sb, block_group,
			desc, bh))) {
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "bg %u: bad block bitmap checksum", block_group);
		if (!EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
			percpu_counter_sub(&sbi->s_freeclusters_counter,
					   grp->bb_free);
		set_bit(EXT4_GROUP_INFO_BBITMAP_CORRUPT_BIT, &grp->bb_state);
		return -EFSBADCRC;
	}
	blk = ext4_valid_block_bitmap(sb, desc, block_group, bh);
	if (unlikely(blk != 0)) {
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "bg %u: block %llu: invalid block bitmap",
			   block_group, blk);
		if (!EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
			percpu_counter_sub(&sbi->s_freeclusters_counter,
					   grp->bb_free);
		set_bit(EXT4_GROUP_INFO_BBITMAP_CORRUPT_BIT, &grp->bb_state);
		return -EFSCORRUPTED;
	}
	set_buffer_verified(bh);
	ext4_unlock_group(sb, block_group);
	return 0;
}
