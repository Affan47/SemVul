check_for_inode_bad_blocks(ext2_inode_scan scan,
					    blk_t *num_blocks)
{
	blk_t	blk = scan->current_block;
	badblocks_list	bb = scan->fs->badblocks;


	if (blk == 0)
		return 0;


	while (blk > bb->list[scan->bad_block_ptr]) {
		if (++scan->bad_block_ptr >= bb->num) {
			scan->scan_flags &= ~EXT2_SF_CHK_BADBLOCKS;
			return 0;
		}
	}


	if (blk == bb->list[scan->bad_block_ptr]) {
		scan->scan_flags |= EXT2_SF_BAD_INODE_BLK;
		*num_blocks = 1;
		if (++scan->bad_block_ptr >= bb->num)
			scan->scan_flags &= ~EXT2_SF_CHK_BADBLOCKS;
		return 0;
	}


	if ((blk + *num_blocks) > bb->list[scan->bad_block_ptr])
		*num_blocks = (int) (bb->list[scan->bad_block_ptr] - blk);

	return 0;
}
