initio_bad_seq(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb;

	printk("initio_bad_seg c=%d\n", host->index);

	if ((scb = host->active) != NULL) {
		initio_unlink_busy_scb(host, scb);
		scb->hastat = HOST_BAD_PHAS;
		scb->tastat = 0;
		initio_append_done_scb(host, scb);
	}
	initio_stop_bm(host);
	initio_reset_scsi(host, 8);
	return initio_post_scsi_rst(host);
}
