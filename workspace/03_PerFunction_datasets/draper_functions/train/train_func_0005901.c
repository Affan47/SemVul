do_capture(struct fp_img_dev *dev)
{
	struct aes4k_dev *aesdev = dev->priv;
	unsigned char *data;
	int r;

	aesdev->img_trf = libusb_alloc_transfer(0);
	if (!aesdev->img_trf) {
		fpi_imgdev_session_error(dev, -EIO);
		return;
	}

	data = g_malloc(DATA_BUFLEN);
	libusb_fill_bulk_transfer(aesdev->img_trf, dev->udev, EP_IN, data,
		DATA_BUFLEN, img_cb, dev, 0);

	r = libusb_submit_transfer(aesdev->img_trf);
	if (r < 0) {
		g_free(data);
		libusb_free_transfer(aesdev->img_trf);
		aesdev->img_trf = NULL;
		fpi_imgdev_session_error(dev, r);
	}
}
