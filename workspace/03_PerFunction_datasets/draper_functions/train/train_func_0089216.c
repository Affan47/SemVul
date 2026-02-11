minix_new_inode(const struct inode *dir, umode_t mode, int *error)
{
	struct super_block *sb = dir->i_sb;
	struct minix_sb_info *sbi = minix_sb(sb);
	struct inode *inode = new_inode(sb);
	struct buffer_head * bh;
	int bits_per_zone = 8 * sb->s_blocksize;
	unsigned long j;
	int i;

	if (!inode) {
		*error = -ENOMEM;
		return NULL;
	}
	j = bits_per_zone;
	bh = NULL;
	*error = -ENOSPC;
	spin_lock(&bitmap_lock);
	for (i = 0; i < sbi->s_imap_blocks; i++) {
		bh = sbi->s_imap[i];
		j = minix_find_first_zero_bit(bh->b_data, bits_per_zone);
		if (j < bits_per_zone)
			break;
	}
	if (!bh || j >= bits_per_zone) {
		spin_unlock(&bitmap_lock);
		iput(inode);
		return NULL;
	}
	if (minix_test_and_set_bit(j, bh->b_data)) {
		spin_unlock(&bitmap_lock);
		printk("minix_new_inode: bit already set\n");
		iput(inode);
		return NULL;
	}
	spin_unlock(&bitmap_lock);
	mark_buffer_dirty(bh);
	j += i * bits_per_zone;
	if (!j || j > sbi->s_ninodes) {
		iput(inode);
		return NULL;
	}
	inode_init_owner(inode, dir, mode);
	inode->i_ino = j;
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME_SEC;
	inode->i_blocks = 0;
	memset(&minix_i(inode)->u, 0, sizeof(minix_i(inode)->u));
	insert_inode_hash(inode);
	mark_inode_dirty(inode);

	*error = 0;
	return inode;
}
