handle_bad_blocks(ext2_filsys fs, badblocks_list bb_list)
{
	dgrp_t			i;
	blk_t			j;
	unsigned 		must_be_good;
	blk_t			blk;
	badblocks_iterate	bb_iter;
	errcode_t		retval;
	blk_t			group_block;
	int			group;
	int			group_bad;

	if (!bb_list)
		return;


	must_be_good = fs->super->s_first_data_block + 1 + fs->desc_blocks;
	for (i = fs->super->s_first_data_block; i <= must_be_good; i++) {
		if (ext2fs_badblocks_list_test(bb_list, i)) {
			fprintf(stderr, _("Block %d in primary "
				"superblock/group descriptor area bad.\n"), i);
			fprintf(stderr, _("Blocks %u through %u must be good "
				"in order to build a filesystem.\n"),
				fs->super->s_first_data_block, must_be_good);
			fputs(_("Aborting....\n"), stderr);
			exit(1);
		}
	}


	group_block = fs->super->s_first_data_block +
		fs->super->s_blocks_per_group;

	for (i = 1; i < fs->group_desc_count; i++) {
		group_bad = 0;
		for (j=0; j < fs->desc_blocks+1; j++) {
			if (ext2fs_badblocks_list_test(bb_list,
						       group_block + j)) {
				if (!group_bad)
					fprintf(stderr,
_("Warning: the backup superblock/group descriptors at block %u contain\n"
"	bad blocks.\n\n"),
						group_block);
				group_bad++;
				group = ext2fs_group_of_blk(fs, group_block+j);
				fs->group_desc[group].bg_free_blocks_count++;
				ext2fs_group_desc_csum_set(fs, group);
				fs->super->s_free_blocks_count++;
			}
		}
		group_block += fs->super->s_blocks_per_group;
	}


	retval = ext2fs_badblocks_list_iterate_begin(bb_list, &bb_iter);
	if (retval) {
		com_err("ext2fs_badblocks_list_iterate_begin", retval,
			_("while marking bad blocks as used"));
		exit(1);
	}
	while (ext2fs_badblocks_list_iterate(bb_iter, &blk))
		ext2fs_mark_block_bitmap(fs->block_map, blk);
	ext2fs_badblocks_list_iterate_end(bb_iter);
}
