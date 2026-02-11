establish_wsp_block_map()
{
	int ewbm_rc = FSCK_OK;
	int32_t blkmap_size_bytes;
	int32_t blkmap_size_in_pages;
	int32_t idx;
	int64_t this_device_offset;

	int I_am_logredo = 0;

	ewbm_rc = establish_wsp_block_map_ctl();

	if (ewbm_rc != FSCK_OK)
		goto ewbm_exit;


	blkmap_size_bytes = agg_recptr->ondev_wsp_byte_length;
	agg_recptr->blkmp_pagecount = blkmap_size_bytes / BYTESPERPAGE;


	agg_recptr->blkmp_agg_offset =
	    agg_recptr->ondev_wsp_byte_offset + BYTESPERPAGE;
	agg_recptr->blkmp_blkmp_offset = 0;
	agg_recptr->blkmp_buf_data_len = 0;
	agg_recptr->blkmp_buf_write = 0;
	agg_recptr->blkmp_blkmp_offset = 0;
	agg_recptr->blkmp_buf_data_len = 0;
	agg_recptr->blkmp_buf_write = 0;

	if (agg_recptr->processing_readonly) {

		ewbm_rc = alloc_wrksp(blkmap_size_bytes, dynstg_blkmap,
				      I_am_logredo,
				      (void **) &(agg_recptr->blkmp_buf_ptr));
		if (ewbm_rc == FSCK_OK) {

			wsp_dynstg_object = 0;
			wsp_dynstg_action = 0;
			agg_recptr->blkmp_buf_length = blkmap_size_bytes;
			agg_recptr->blkmp_buf_data_len =
			    agg_recptr->blkmp_buf_length;
		}
		goto ewbm_exit;
	}

	ewbm_rc = alloc_wrksp(BLKMP_IO_BUFSIZE, dynstg_blkmap_buf, I_am_logredo,
			      (void **) &(agg_recptr->blkmp_buf_ptr));
	if (ewbm_rc != FSCK_OK)
		goto ewbm_exit;


	agg_recptr->blkmp_buf_length = BLKMP_IO_BUFSIZE;
	agg_recptr->blkmp_buf_data_len = agg_recptr->blkmp_buf_length;
	ewbm_rc = blkmap_put_ctl_page(agg_recptr->blkmp_ctlptr);
	if (ewbm_rc != FSCK_OK)
		goto ewbm_exit;


	blkmap_size_in_pages = blkmap_size_bytes / BYTESPERPAGE;

	ujfs_swap_fsck_blk_map_page(agg_recptr->blkmp_buf_ptr);
	for (idx = 1; ((idx < blkmap_size_in_pages) &&
	     (ewbm_rc == FSCK_OK)); idx++) {

		this_device_offset = agg_recptr->ondev_wsp_byte_offset +
		    (idx * BYTESPERPAGE);


		ewbm_rc = ujfs_rw_diskblocks(Dev_IOPort, this_device_offset,
				    BYTESPERPAGE,
				    (void *) agg_recptr->blkmp_buf_ptr, PUT);
		if (ewbm_rc != FSCK_OK) {


			fsck_send_msg(fsck_URCVWRT, fsck_ref_msg(fsck_metadata),
				      Vol_Label, 1);


			fsck_send_msg(fsck_ERRONWSP, ewbm_rc, ewbm_rc, fsck_WRITE,
				      (long long)this_device_offset,
				      BYTESPERPAGE, -1);
		}
	}

	ujfs_swap_fsck_blk_map_page(agg_recptr->blkmp_buf_ptr);

      ewbm_exit:
	return (ewbm_rc);
}
