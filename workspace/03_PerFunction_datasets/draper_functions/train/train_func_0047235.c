fat_hash_init(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	int i;

	spin_lock_init(&sbi->inode_hash_lock);
	for (i = 0; i < FAT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&sbi->inode_hashtable[i]);
}
