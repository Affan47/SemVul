fat_mirror_bhs(struct super_block *sb, struct buffer_head **bhs,
			  int nr_bhs)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *c_bh;
	int err, n, copy;

	err = 0;
	for (copy = 1; copy < sbi->fats; copy++) {
		sector_t backup_fat = sbi->fat_length * copy;

		for (n = 0; n < nr_bhs; n++) {
			c_bh = sb_getblk(sb, backup_fat + bhs[n]->b_blocknr);
			if (!c_bh) {
				err = -ENOMEM;
				goto error;
			}
			memcpy(c_bh->b_data, bhs[n]->b_data, sb->s_blocksize);
			set_buffer_uptodate(c_bh);
			mark_buffer_dirty_inode(c_bh, sbi->fat_inode);
			if (sb->s_flags & MS_SYNCHRONOUS)
				err = sync_dirty_buffer(c_bh);
			brelse(c_bh);
			if (err)
				goto error;
		}
	}
error:
	return err;
}
