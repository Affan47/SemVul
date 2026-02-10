capture_read_data_cb(struct libusb_transfer *transfer)
{
	struct fpi_ssm *ssm = transfer->user_data;
	struct fp_img_dev *dev = ssm->priv;
	struct aes2550_dev *aesdev = dev->priv;
	unsigned char *data = transfer->buffer;
	int r;

	if (transfer->status != LIBUSB_TRANSFER_COMPLETED) {
		fp_dbg("request is not completed, %d", transfer->status);
		fpi_ssm_mark_aborted(ssm, -EIO);
		goto out;
	}

	fp_dbg("request completed, len: %.4x", transfer->actual_length);
	if (transfer->actual_length >= 2)
		fp_dbg("data: %.2x %.2x", (int)data[0], (int)data[1]);

	switch (transfer->actual_length) {
		case AES2550_STRIP_SIZE:
			r = process_strip_data(ssm, data);
			if (r < 0) {
				fp_dbg("Processing strip data failed: %d", r);
				fpi_ssm_mark_aborted(ssm, -EPROTO);
				goto out;
			}
			aesdev->heartbeat_cnt = 0;
			fpi_ssm_jump_to_state(ssm, CAPTURE_READ_DATA);
			break;
		case AES2550_HEARTBEAT_SIZE:
			if (data[0] == AES2550_HEARTBEAT_MAGIC) {

				aesdev->heartbeat_cnt++;
				if (aesdev->heartbeat_cnt == 3) {


					fp_dbg("Got 3 heartbeats => finger removed");
					fpi_ssm_next_state(ssm);
				} else {
					fpi_ssm_jump_to_state(ssm, CAPTURE_READ_DATA);
				}
			}
			break;
		default:
			fp_dbg("Short frame %d, skip", transfer->actual_length);
			fpi_ssm_jump_to_state(ssm, CAPTURE_READ_DATA);
			break;
	}
out:
	g_free(transfer->buffer);
	libusb_free_transfer(transfer);
}
