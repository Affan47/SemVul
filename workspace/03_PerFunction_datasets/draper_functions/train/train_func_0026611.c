AIS_inode_check(struct dinode *primary_inoptr,
		    struct dinode *secondary_inoptr,
		    int32_t tree_offset,
		    int32_t tree_size, int *inconsistency_detected)
{
	xtpage_t *primary_root, *secondary_root;
	int32_t result1, result2, result3, result4, result5, result6;

	*inconsistency_detected =
	    ((primary_inoptr->di_inostamp != secondary_inoptr->di_inostamp)
	     || (primary_inoptr->di_fileset != secondary_inoptr->di_fileset)
	     || (primary_inoptr->di_number != secondary_inoptr->di_number)
	     || (primary_inoptr->di_gen != secondary_inoptr->di_gen)
	     || (primary_inoptr->di_size != secondary_inoptr->di_size)
	     || (primary_inoptr->di_nblocks != secondary_inoptr->di_nblocks)
	     || (primary_inoptr->di_nlink != secondary_inoptr->di_nlink)
	     || (primary_inoptr->di_uid != secondary_inoptr->di_uid)
	     || (primary_inoptr->di_gid != secondary_inoptr->di_gid)
	     || (primary_inoptr->di_mode != secondary_inoptr->di_mode)
	     || (primary_inoptr->di_next_index !=
		 secondary_inoptr->di_next_index));

	if (!(*inconsistency_detected)) {
		if (tree_offset == 0) {
			result1 = 0;
		} else {

			primary_root =
			    (xtpage_t *) (((char *) primary_inoptr) +
					  tree_offset);
			secondary_root =
			    (xtpage_t *) (((char *) primary_inoptr) +
					  tree_offset);
			result1 =
			    memcmp((void *) primary_root,
				   (void *) secondary_root, tree_size);
		}

		result2 = memcmp((void *) &(primary_inoptr->di_atime),
				 (void *) &(secondary_inoptr->di_atime),
				 sizeof (primary_inoptr->di_atime));
		result3 = memcmp((void *) &(primary_inoptr->di_ctime),
				 (void *) &(secondary_inoptr->di_ctime),
				 sizeof (primary_inoptr->di_ctime));
		result4 = memcmp((void *) &(primary_inoptr->di_mtime),
				 (void *) &(secondary_inoptr->di_mtime),
				 sizeof (primary_inoptr->di_mtime));
		result5 = memcmp((void *) &(primary_inoptr->di_otime),
				 (void *) &(secondary_inoptr->di_otime),
				 sizeof (primary_inoptr->di_otime));
		result6 = memcmp((void *) &(primary_inoptr->di_ea),
				 (void *) &(secondary_inoptr->di_ea),
				 sizeof (primary_inoptr->di_ea));

		*inconsistency_detected = (result1 || result2 || result3 ||
					   result4 || result5 || result6);
	}
	if (!(*inconsistency_detected)) {
		*inconsistency_detected = memcmp((void *) &(sb_ptr->s_ait2),
						 (void *) &(secondary_inoptr->
							    di_ixpxd),
						 sizeof (pxd_t));
	}
	if ((*inconsistency_detected)) {


		fsck_send_msg(fsck_INCONSIST2NDRY, "2");
	}
	return (FSCK_OK);
}
