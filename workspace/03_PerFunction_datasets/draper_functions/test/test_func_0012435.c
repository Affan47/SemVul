rtl2832_sdr_free_urbs(struct rtl2832_sdr_dev *dev)
{
	struct platform_device *pdev = dev->pdev;
	int i;

	rtl2832_sdr_kill_urbs(dev);

	for (i = dev->urbs_initialized - 1; i >= 0; i--) {
		if (dev->urb_list[i]) {
			dev_dbg(&pdev->dev, "free urb=%d\n", i);

			usb_free_urb(dev->urb_list[i]);
		}
	}
	dev->urbs_initialized = 0;

	return 0;
}
