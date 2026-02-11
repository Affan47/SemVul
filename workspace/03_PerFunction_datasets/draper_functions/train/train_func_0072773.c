ujfs_rwinode(FILE *fp,
		 struct dinode *di,
		 uint32_t inum,
		 int32_t mode,
		 int32_t fs_block_size,
		 uint32_t which_table,
		 uint32_t sb_flag)
{
	struct dinode map_inode;
	int rc;
	int64_t inode_extent_address, inode_address;
	int64_t map_inode_address;
	uint32_t iag_key;
	int32_t iag_inode_num, inode_ext_index;
	struct iag iag_for_inode;
	int64_t iag_address;
	int32_t l2nbperpage = log2shift(PSIZE / fs_block_size);


	if (which_table == AGGREGATE_I) {


		if (inum >= NUM_INODE_PER_EXTENT) {
			fprintf(stderr,
				"Internal error: %s(%d): Aggregate inode out of range (%d)\n",
				__FILE__, __LINE__, inum);
			return ERROR_INVALID_ACCESS;
		}

		inode_address = (inum * sizeof (struct dinode)) + AGGR_INODE_TABLE_START;
	} else if (which_table == FILESYSTEM_I) {


		iag_key = INOTOIAG(inum);


		map_inode_address = AGGR_INODE_TABLE_START + (which_table * sizeof (struct dinode));
		rc = ujfs_rw_diskblocks(fp, map_inode_address, sizeof (struct dinode), &map_inode, GET);


		ujfs_swap_dinode(&map_inode, GET, sb_flag);

		if (rc != 0)
			return (rc);


		rc = ujfs_rwdaddr(fp, &iag_address, &map_inode,
				  IAGTOLBLK(iag_key, l2nbperpage), GET, fs_block_size);
		if (rc != 0)
			return (rc);


		rc = ujfs_rw_diskblocks(fp, iag_address, sizeof (struct iag), &iag_for_inode, GET);


		ujfs_swap_iag(&iag_for_inode);

		if (rc != 0)
			return (rc);


		iag_inode_num = inum % NUM_INODE_PER_IAG;


		inode_ext_index = iag_inode_num / NUM_INODE_PER_EXTENT;


		inode_extent_address = addressPXD(&(iag_for_inode.inoext[inode_ext_index]));
		inode_extent_address *= fs_block_size;
		inode_address = (inum % NUM_INODE_PER_EXTENT * sizeof (struct dinode)) + inode_extent_address;
	} else {
		fprintf(stderr, "Internal error: %s(%d): Bad map inode number (%d)\n",
			__FILE__, __LINE__, which_table);
		return ERROR_INVALID_HANDLE;
	}


	if (mode == PUT)
		ujfs_swap_dinode(di, PUT, sb_flag);

	rc = ujfs_rw_diskblocks(fp, inode_address, sizeof (struct dinode), di, mode);


	ujfs_swap_dinode(di, GET, sb_flag);

	return rc;
}
