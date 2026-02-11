enroll_iterate_cmd_cb(struct libusb_transfer *transfer)
{
	struct fp_dev *dev = transfer->user_data;

	if (transfer->status != LIBUSB_TRANSFER_COMPLETED) {
		fpi_drvcb_enroll_stage_completed(dev, -EIO, NULL, NULL);
	} else if (transfer->length != transfer->actual_length) {
		fpi_drvcb_enroll_stage_completed(dev, -EPROTO, NULL, NULL);
	} else {
		int r = read_msg_async(dev, enroll_iterate_msg_cb, NULL);
		if (r < 0)
			fpi_drvcb_enroll_stage_completed(dev, r, NULL, NULL);
	}
	libusb_free_transfer(transfer);
}
