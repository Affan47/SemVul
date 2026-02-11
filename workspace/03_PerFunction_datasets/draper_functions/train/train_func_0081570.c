phase8_processing()
{
	int p8_rc = FSCK_OK;

	if (agg_recptr->processing_readwrite) {

		fsck_send_msg(fsck_PHASE8R);
		p8_rc = rebuild_blkall_map();
	} else {

		fsck_send_msg(fsck_PHASE8V);
		p8_rc = verify_blkall_map();
	}
	if (p8_rc != FSCK_OK) {
		agg_recptr->fsck_is_done = 1;
		exit_value = FSCK_ERRORS_UNCORRECTED;
	}
	return (p8_rc);
}
