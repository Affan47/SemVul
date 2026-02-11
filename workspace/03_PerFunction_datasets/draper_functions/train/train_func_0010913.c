fscklog_init()
{
	int fli_rc = FSCK_OK;
	int64_t log_bytes_left;
	struct fsck_blk_map_page *tmpbuf_addr = NULL;
	struct fsck_blk_map_page *tmp_buf_ptr;
	uint32_t tmp_buf_data_len;
	int64_t tmp_agg_offset;
	int64_t tmp_log_offset;

	if (agg_recptr->processing_readwrite) {


		tmpbuf_addr =
		    (struct fsck_blk_map_page *) malloc(FSCKLOG_BUFSIZE);

		if (tmpbuf_addr == NULL) {


			fsck_send_msg(fsck_CANTINITSVCLOG);
		} else {

			agg_recptr->initializing_fscklog = 1;
			memset((void *) tmpbuf_addr, 0, FSCKLOG_BUFSIZE);


			tmp_buf_ptr = agg_recptr->fscklog_buf_ptr;
			tmp_buf_data_len = agg_recptr->fscklog_buf_data_len;
			tmp_agg_offset = agg_recptr->fscklog_agg_offset;
			tmp_log_offset = agg_recptr->fscklog_log_offset;


			agg_recptr->fscklog_buf_ptr = tmpbuf_addr;
			agg_recptr->fscklog_buf_data_len = FSCKLOG_BUFSIZE;

			log_bytes_left =
			    (agg_recptr->ondev_fscklog_byte_length / 2) -
			    agg_recptr->fscklog_log_offset;
			while (log_bytes_left >= agg_recptr->fscklog_buf_length) {
				fscklog_put_buffer();
				log_bytes_left =
				    (agg_recptr->ondev_fscklog_byte_length /
				     2) - agg_recptr->fscklog_log_offset;
			}

			free((void *) tmpbuf_addr);


			agg_recptr->fscklog_buf_ptr = tmp_buf_ptr;
			agg_recptr->fscklog_buf_data_len = tmp_buf_data_len;
			agg_recptr->fscklog_agg_offset = tmp_agg_offset;
			agg_recptr->fscklog_log_offset = tmp_log_offset;

			agg_recptr->initializing_fscklog = 0;
		}
	}
	return (fli_rc);
}
