record_other_ait()
{
	int roa_rc = FSCK_OK;
	int64_t start_block, end_block;
	uint32_t length_in_agg_blocks;


	if (agg_recptr->primary_ait_4part1) {

		start_block = addressPXD(&(sb_ptr->s_aim2));
		length_in_agg_blocks = lengthPXD(&(sb_ptr->s_aim2));
	} else {

		start_block = AIMAP_OFF / sb_ptr->s_bsize;
		length_in_agg_blocks =
		    (AITBL_OFF - AIMAP_OFF) / sb_ptr->s_bsize;
	}

	end_block = start_block + length_in_agg_blocks - 1;
	roa_rc = blkall_increment_owners(start_block, end_block, NULL);


	if (agg_recptr->primary_ait_4part1) {

		start_block = addressPXD(&(sb_ptr->s_ait2));
		length_in_agg_blocks = lengthPXD(&(sb_ptr->s_ait2));
	} else {

		start_block = AITBL_OFF / sb_ptr->s_bsize;
		length_in_agg_blocks = INODE_EXTENT_SIZE / sb_ptr->s_bsize;
	}

	end_block = start_block + length_in_agg_blocks - 1;
	roa_rc = blkall_increment_owners(start_block, end_block, NULL);

	return (roa_rc);
}
