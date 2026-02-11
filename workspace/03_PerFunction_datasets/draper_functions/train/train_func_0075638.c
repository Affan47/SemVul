affs_kill_sb(struct super_block *sb)
{
	struct affs_sb_info *sbi = AFFS_SB(sb);
	kill_block_super(sb);
	if (sbi) {
		affs_free_bitmap(sb);
		affs_brelse(sbi->s_root_bh);
		kfree(sbi->s_prefix);
		mutex_destroy(&sbi->s_bmlock);
		kfree(sbi);
	}
}
