dev_init(struct fp_dev *dev, unsigned long driver_data)
{
	struct upeke2_dev *upekdev = NULL;
	int r;

	r = libusb_claim_interface(dev->udev, 0);
	if (r < 0)
		return r;

	upekdev = g_malloc(sizeof(*upekdev));
	upekdev->seq = 0xf0;
	dev->priv = upekdev;
	dev->nr_enroll_stages = 5;

	fpi_drvcb_open_complete(dev, 0);
	return 0;
}
