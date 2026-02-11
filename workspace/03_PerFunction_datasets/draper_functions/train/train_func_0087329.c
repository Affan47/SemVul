capture_iterate(struct fpi_ssm *ssm)
{
	struct fp_img_dev *dev = ssm->priv;
	struct v5s_dev *vdev = dev->priv;
	int iteration = vdev->capture_iteration;
	struct libusb_transfer *transfer = libusb_alloc_transfer(0);
	int r;

	if (!transfer) {
		fpi_ssm_mark_aborted(ssm, -ENOMEM);
		return;
	}

	libusb_fill_bulk_transfer(transfer, dev->udev, EP_IN,
		vdev->capture_img->data + (RQ_SIZE * iteration), RQ_SIZE,
		capture_cb, ssm, CTRL_TIMEOUT);
	transfer->flags = LIBUSB_TRANSFER_SHORT_NOT_OK;
	r = libusb_submit_transfer(transfer);
	if (r < 0) {
		libusb_free_transfer(transfer);
		fpi_ssm_mark_aborted(ssm, r);
	}
}
