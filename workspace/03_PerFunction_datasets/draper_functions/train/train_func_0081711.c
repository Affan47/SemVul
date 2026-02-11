omfs_dir_is_empty(struct inode *inode)
{
	int nbuckets = (inode->i_size - OMFS_DIR_START) / 8;
	struct buffer_head *bh;
	u64 *ptr;
	int i;

	bh = omfs_bread(inode->i_sb, inode->i_ino);

	if (!bh)
		return 0;

	ptr = (u64 *) &bh->b_data[OMFS_DIR_START];

	for (i = 0; i < nbuckets; i++, ptr++)
		if (*ptr != ~0)
			break;

	brelse(bh);
	return *ptr != ~0;
}
