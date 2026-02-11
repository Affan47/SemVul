capture_set_idle_reqs_cb(struct libusb_transfer *transfer)
{
	struct fpi_ssm *ssm = transfer->user_data;
	struct fp_img_dev *dev = ssm->priv;
	struct aes2550_dev *aesdev = dev->priv;

	if ((transfer->status == LIBUSB_TRANSFER_COMPLETED) &&
		(transfer->length == transfer->actual_length)) {
		struct fp_img *img;

		aesdev->strips = g_slist_reverse(aesdev->strips);
		img = aes_assemble(aesdev->strips, aesdev->strips_len,
			FRAME_WIDTH, FRAME_HEIGHT);
		g_slist_free_full(aesdev->strips, g_free);
		aesdev->strips = NULL;
		aesdev->strips_len = 0;
		fpi_imgdev_image_captured(dev, img);
		fpi_imgdev_report_finger_status(dev, FALSE);

		fpi_ssm_mark_completed(ssm);
	} else {
		fpi_ssm_mark_aborted(ssm, -EIO);
	}
	libusb_free_transfer(transfer);
}
