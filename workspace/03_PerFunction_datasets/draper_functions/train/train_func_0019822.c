free_usb_address(struct r8a66597 *r8a66597,
			     struct r8a66597_device *dev, int reset)
{
	int port;

	if (!dev)
		return;

	dev_dbg(&dev->udev->dev, "free_addr: addr=%d\n", dev->address);

	dev->state = USB_STATE_DEFAULT;
	r8a66597->address_map &= ~(1 << dev->address);
	dev->address = 0;


	if (reset)
		dev_set_drvdata(&dev->udev->dev, NULL);
	list_del(&dev->device_list);
	kfree(dev);

	for (port = 0; port < r8a66597->max_root_hub; port++) {
		if (r8a66597->root_hub[port].dev == dev) {
			r8a66597->root_hub[port].dev = NULL;
			break;
		}
	}
}
