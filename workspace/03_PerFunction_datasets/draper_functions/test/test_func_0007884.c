start_stop_endio(struct request *req, int error)
{
	struct hp_sw_dh_data *h = req->end_io_data;
	unsigned err = SCSI_DH_OK;

	if (error || host_byte(req->errors) != DID_OK ||
			msg_byte(req->errors) != COMMAND_COMPLETE) {
		sdev_printk(KERN_WARNING, h->sdev,
			    "%s: sending start_stop_unit failed with %x\n",
			    HP_SW_NAME, req->errors);
		err = SCSI_DH_IO;
		goto done;
	}

	if (req->sense_len > 0) {
		err = start_done(h->sdev, h->sense);
		if (err == SCSI_DH_RETRY) {
			err = SCSI_DH_IO;
			if (--h->retry_cnt) {
				blk_put_request(req);
				err = hp_sw_start_stop(h);
				if (err == SCSI_DH_OK)
					return;
			}
		}
	}
done:
	req->end_io_data = NULL;
	__blk_put_request(req->q, req);
	if (h->callback_fn) {
		h->callback_fn(h->callback_data, err);
		h->callback_fn = h->callback_data = NULL;
	}
	return;

}
