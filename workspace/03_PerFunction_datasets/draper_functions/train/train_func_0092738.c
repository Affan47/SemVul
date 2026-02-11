disconnect_inode(e2fsck_t ctx, ext2_ino_t i,
			    struct ext2_inode *inode)
{
	ext2_filsys fs = ctx->fs;
	struct problem_context	pctx;
	__u32 eamagic = 0;
	int extra_size = 0;

	if (EXT2_INODE_SIZE(fs->super) > EXT2_GOOD_OLD_INODE_SIZE) {
		e2fsck_read_inode_full(ctx, i, inode,EXT2_INODE_SIZE(fs->super),
				       "pass4: disconnect_inode");
		extra_size = ((struct ext2_inode_large *)inode)->i_extra_isize;
	} else {
		e2fsck_read_inode(ctx, i, inode, "pass4: disconnect_inode");
	}
	clear_problem_context(&pctx);
	pctx.ino = i;
	pctx.inode = inode;

	if (EXT2_INODE_SIZE(fs->super) -EXT2_GOOD_OLD_INODE_SIZE -extra_size >0)
		eamagic = *(__u32 *)(((char *)inode) +EXT2_GOOD_OLD_INODE_SIZE +
				     extra_size);


	if (!inode->i_blocks && eamagic != EXT2_EXT_ATTR_MAGIC &&
	    (LINUX_S_ISREG(inode->i_mode) || LINUX_S_ISDIR(inode->i_mode))) {
		if (fix_problem(ctx, PR_4_ZERO_LEN_INODE, &pctx)) {
			e2fsck_clear_inode(ctx, i, inode, 0,
					   "disconnect_inode");


			e2fsck_read_bitmaps(ctx);
			ext2fs_inode_alloc_stats2(fs, i, -1,
						  LINUX_S_ISDIR(inode->i_mode));
			return 0;
		}
	}


	if (fix_problem(ctx, PR_4_UNATTACHED_INODE, &pctx)) {
		if (e2fsck_reconnect_file(ctx, i))
			ext2fs_unmark_valid(fs);
	} else {


		ext2fs_unmark_valid(fs);
		return 1;
	}
	return 0;
}
