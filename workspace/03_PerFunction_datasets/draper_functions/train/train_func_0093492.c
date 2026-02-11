create_fileset(FILE *dev_ptr, int aggr_block_size,
			  int64_t start_block, unsigned inostamp)
{
	int rc;
	int64_t inode_table_loc, inode_map_loc;
	int inode_table_size, inode_map_size;


	inode_map_size = SIZE_OF_MAP_PAGE << 1;
#ifdef ONE_FILESET_PER_AGGR


	inode_map_loc = start_block + INODE_EXTENT_SIZE / aggr_block_size;
#else
	inode_map_loc = get_space(inode_map_size);
#endif


	rc = init_fileset_inodes(aggr_block_size, dev_ptr, inode_map_loc,
				 inode_map_size, start_block, inostamp);
	if (rc != 0)
		return (rc);


	rc = init_fileset_inode_table(aggr_block_size, dev_ptr,
				      &inode_table_loc, &inode_table_size,
				      start_block, inode_map_loc, inostamp);
	if (rc != 0)
		return (rc);


	rc = init_inode_map(aggr_block_size, dev_ptr, inode_table_loc,
			    inode_table_size, inode_map_loc, inode_map_size,
			    (ACL_I + 1), AGsize, FILESYSTEM_I);

	return rc;
}
