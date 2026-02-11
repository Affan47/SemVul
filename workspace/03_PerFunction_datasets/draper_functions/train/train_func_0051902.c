pass1c(e2fsck_t ctx, char *block_buf)
{
	ext2_filsys fs = ctx->fs;
	struct search_dir_struct sd;
	struct problem_context pctx;

	clear_problem_context(&pctx);

	if (!(ctx->options & E2F_OPT_PREEN))
		fix_problem(ctx, PR_1C_PASS_HEADER, &pctx);


	sd.count = dup_inode_count - dup_inode_founddir;
	sd.first_inode = EXT2_FIRST_INODE(fs->super);
	sd.max_inode = fs->super->s_inodes_count;
	ext2fs_dblist_dir_iterate(fs->dblist, 0, block_buf,
				  search_dirent_proc, &sd);
}
