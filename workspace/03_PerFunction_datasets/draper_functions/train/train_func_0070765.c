inode_write_alias(struct super_block *sb,
		struct logfs_block *block, write_alias_t *write_one_alias)
{
	struct inode *inode = block->inode;
	struct logfs_inode *li = logfs_inode(inode);
	unsigned long pos;
	u64 ino , bix;
	__be64 val;
	level_t level;
	int err;

	for (pos = 0; ; pos++) {
		pos = fnb(block->alias_map, LOGFS_BLOCK_FACTOR, pos);
		if (pos >= LOGFS_EMBEDDED_FIELDS + INODE_POINTER_OFS)
			return 0;

		switch (pos) {
		case INODE_HEIGHT_OFS:
			val = inode_val0(inode);
			break;
		case INODE_USED_OFS:
			val = cpu_to_be64(li->li_used_bytes);
			break;
		case INODE_SIZE_OFS:
			val = cpu_to_be64(i_size_read(inode));
			break;
		case INODE_POINTER_OFS ... INODE_POINTER_OFS + LOGFS_EMBEDDED_FIELDS - 1:
			val = cpu_to_be64(li->li_data[pos - INODE_POINTER_OFS]);
			break;
		default:
			BUG();
		}

		ino = LOGFS_INO_MASTER;
		bix = inode->i_ino;
		level = LEVEL(0);
		err = write_one_alias(sb, ino, bix, level, pos, val);
		if (err)
			return err;
	}
}
