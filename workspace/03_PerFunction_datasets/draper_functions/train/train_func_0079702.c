check_inode_end(e2fsck_t ctx)
{
	ext2_filsys fs = ctx->fs;
	ext2_ino_t	end, save_inodes_count, i;
	struct problem_context	pctx;

	clear_problem_context(&pctx);

	end = EXT2_INODES_PER_GROUP(fs->super) * fs->group_desc_count;
	pctx.errcode = ext2fs_fudge_inode_bitmap_end(fs->inode_map, end,
						     &save_inodes_count);
	if (pctx.errcode) {
		pctx.num = 1;
		fix_problem(ctx, PR_5_FUDGE_BITMAP_ERROR, &pctx);
		ctx->flags |= E2F_FLAG_ABORT;
		return;
	}
	if (save_inodes_count == end)
		return;


	for (i = save_inodes_count + 1; i <= end && i > save_inodes_count; i++) {
		if (!ext2fs_test_inode_bitmap(fs->inode_map, i)) {
			if (fix_problem(ctx, PR_5_INODE_BMAP_PADDING, &pctx)) {
				for (; i <= end; i++)
					ext2fs_mark_inode_bitmap(fs->inode_map,
								 i);
				ext2fs_mark_ib_dirty(fs);
			} else
				ext2fs_unmark_valid(fs);
			break;
		}
	}

	pctx.errcode = ext2fs_fudge_inode_bitmap_end(fs->inode_map,
						     save_inodes_count, 0);
	if (pctx.errcode) {
		pctx.num = 2;
		fix_problem(ctx, PR_5_FUDGE_BITMAP_ERROR, &pctx);
		ctx->flags |= E2F_FLAG_ABORT;
		return;
	}
}
