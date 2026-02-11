add_bad_block(FILE *dev_ptr, int64_t thisblk, int aggr_block_size,
			 struct dinode *bb_inode)
{
	int rc = 0;


	rc = markit(thisblk, ALLOC | BADBLOCK);
	if (rc != 0) {
		return (rc);
	}

	rc = xtAppend(dev_ptr, bb_inode, bb_inode->di_size / aggr_block_size,
		      thisblk, 1, badblock_pages, aggr_block_size);

	if (!rc) {
		bb_inode->di_size += aggr_block_size;
		bb_inode->di_nblocks++;
	}

	return rc;
}
