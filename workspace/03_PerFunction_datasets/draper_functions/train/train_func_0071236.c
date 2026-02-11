process_pass1b_block(ext2_filsys fs EXT2FS_ATTR((unused)),
				blk_t	*block_nr,
				e2_blkcnt_t blockcnt EXT2FS_ATTR((unused)),
				blk_t ref_blk EXT2FS_ATTR((unused)),
				int ref_offset EXT2FS_ATTR((unused)),
				void *priv_data)
{
	struct process_block_struct *p;
	e2fsck_t ctx;

	if (HOLE_BLKADDR(*block_nr))
		return 0;
	p = (struct process_block_struct *) priv_data;
	ctx = p->ctx;

	if (!ext2fs_test_block_bitmap(ctx->block_dup_map, *block_nr))
		return 0;


	if (p->ino != EXT2_BAD_INO) {
		p->pctx->blk = *block_nr;
		fix_problem(ctx, PR_1B_DUP_BLOCK, p->pctx);
	}
	p->dup_blocks++;
	ext2fs_mark_inode_bitmap(inode_dup_map, p->ino);

	add_dupe(ctx, p->ino, *block_nr, p->inode);

	return 0;
}
