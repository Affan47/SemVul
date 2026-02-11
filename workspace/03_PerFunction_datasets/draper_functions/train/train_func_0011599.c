finger_det_reqs_cb(struct fp_img_dev *dev, int result,
	void *user_data)
{
	struct libusb_transfer *transfer;
	unsigned char *data;
	int r;

	if (result) {
		fpi_imgdev_session_error(dev, result);
		return;
	}

	transfer = libusb_alloc_transfer(0);
	if (!transfer) {
		fpi_imgdev_session_error(dev, -ENOMEM);
		return;
	}

	data = g_malloc(20);
	libusb_fill_bulk_transfer(transfer, dev->udev, EP_IN, data, 20,
		finger_det_data_cb, dev, BULK_TIMEOUT);

	r = libusb_submit_transfer(transfer);
	if (r < 0) {
		g_free(data);
		libusb_free_transfer(transfer);
		fpi_imgdev_session_error(dev, r);
	}
}
