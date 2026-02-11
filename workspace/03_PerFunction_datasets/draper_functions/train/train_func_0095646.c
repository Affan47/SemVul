establish_agg_workspace()
{
	int eaw_rc = FSCK_OK;
	uint32_t mapsize_bytes;
	int I_am_logredo = 0;


	eaw_rc = establish_wsp_block_map();

	if (eaw_rc == FSCK_OK) {

		agg_recptr->agg_imap.num_iags = 1;
		agg_recptr->agg_imap.bkd_inodes = INOSPEREXT;
		agg_recptr->agg_imap.unused_bkd_inodes = INOSPEREXT - 4;


		agg_recptr->inode_count = INOSPEREXT;


		mapsize_bytes =
		    agg_recptr->agg_imap.num_iags *
		    sizeof (struct fsck_iag_record);
		eaw_rc =
		    alloc_wrksp(mapsize_bytes, dynstg_agg_iagtbl, I_am_logredo,
				(void **) &(agg_recptr->agg_imap.iag_tbl));
		if (eaw_rc == FSCK_OK) {


			eaw_rc =
			    alloc_wrksp(inode_tbl_length, dynstg_ait_inotbl,
					I_am_logredo,
					(void **) &(agg_recptr->AIT_ext0_tbl));
			memcpy((void *) &(agg_recptr->AIT_ext0_tbl->eyecatcher),
			       (void *) "InodeTbl", 8);
		}
	}
	return (eaw_rc);
}
