new_table_block(e2fsck_t ctx, blk_t first_block, int group,
			    const char *name, int num, blk_t *new_block)
{
	ext2_filsys fs = ctx->fs;
	dgrp_t		last_grp;
	blk_t		old_block = *new_block;
	blk_t		last_block;
	int		i, is_flexbg, flexbg, flexbg_size;
	char		*buf;
	struct problem_context	pctx;

	clear_problem_context(&pctx);

	pctx.group = group;
	pctx.blk = old_block;
	pctx.str = name;


	is_flexbg = EXT2_HAS_INCOMPAT_FEATURE(fs->super,
					      EXT4_FEATURE_INCOMPAT_FLEX_BG);
	if (is_flexbg) {
		flexbg_size = 1 << fs->super->s_log_groups_per_flex;
		flexbg = group / flexbg_size;
		first_block = ext2fs_group_first_block(fs,
						       flexbg_size * flexbg);
		last_grp = group | (flexbg_size - 1);
		if (last_grp > fs->group_desc_count)
			last_grp = fs->group_desc_count;
		last_block = ext2fs_group_last_block(fs, last_grp);
	} else
		last_block = ext2fs_group_last_block(fs, group);
	pctx.errcode = ext2fs_get_free_blocks(fs, first_block, last_block,
					      num, ctx->block_found_map,
					      new_block);
	if (is_flexbg && (pctx.errcode == EXT2_ET_BLOCK_ALLOC_FAIL))
		pctx.errcode = ext2fs_get_free_blocks(fs,
				fs->super->s_first_data_block,
				fs->super->s_blocks_count,
				num, ctx->block_found_map, new_block);
	if (pctx.errcode) {
		pctx.num = num;
		fix_problem(ctx, PR_1_RELOC_BLOCK_ALLOCATE, &pctx);
		ext2fs_unmark_valid(fs);
		ctx->flags |= E2F_FLAG_ABORT;
		return;
	}
	pctx.errcode = ext2fs_get_mem(fs->blocksize, &buf);
	if (pctx.errcode) {
		fix_problem(ctx, PR_1_RELOC_MEMORY_ALLOCATE, &pctx);
		ext2fs_unmark_valid(fs);
		ctx->flags |= E2F_FLAG_ABORT;
		return;
	}
	ext2fs_mark_super_dirty(fs);
	fs->flags &= ~EXT2_FLAG_MASTER_SB_ONLY;
	pctx.blk2 = *new_block;
	fix_problem(ctx, (old_block ? PR_1_RELOC_FROM_TO :
			  PR_1_RELOC_TO), &pctx);
	pctx.blk2 = 0;
	for (i = 0; i < num; i++) {
		pctx.blk = i;
		ext2fs_mark_block_bitmap(ctx->block_found_map, (*new_block)+i);
		if (old_block) {
			pctx.errcode = io_channel_read_blk(fs->io,
				   old_block + i, 1, buf);
			if (pctx.errcode)
				fix_problem(ctx, PR_1_RELOC_READ_ERR, &pctx);
		} else
			memset(buf, 0, fs->blocksize);

		pctx.blk = (*new_block) + i;
		pctx.errcode = io_channel_write_blk(fs->io, pctx.blk,
					      1, buf);
		if (pctx.errcode)
			fix_problem(ctx, PR_1_RELOC_WRITE_ERR, &pctx);
	}
	ext2fs_free_mem(&buf);
}
