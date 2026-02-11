e2fsck_adjust_inode_count(e2fsck_t ctx, ext2_ino_t ino, int adj)
{
	ext2_filsys fs = ctx->fs;
	errcode_t		retval;
	struct ext2_inode 	inode;

	if (!ino)
		return 0;

	retval = ext2fs_read_inode(fs, ino, &inode);
	if (retval)
		return retval;

#if 0
	printf("Adjusting link count for inode %lu by %d (from %d)\n", ino, adj,
	       inode.i_links_count);
#endif

	if (adj == 1) {
		ext2fs_icount_increment(ctx->inode_count, ino, 0);
		if (inode.i_links_count == (__u16) ~0)
			return 0;
		ext2fs_icount_increment(ctx->inode_link_info, ino, 0);
		inode.i_links_count++;
	} else if (adj == -1) {
		ext2fs_icount_decrement(ctx->inode_count, ino, 0);
		if (inode.i_links_count == 0)
			return 0;
		ext2fs_icount_decrement(ctx->inode_link_info, ino, 0);
		inode.i_links_count--;
	}

	retval = ext2fs_write_inode(fs, ino, &inode);
	if (retval)
		return retval;

	return 0;
}
