stub_device_alloc(struct usb_device *udev)
{
	struct stub_device *sdev;
	int busnum = udev->bus->busnum;
	int devnum = udev->devnum;

	dev_dbg(&udev->dev, "allocating stub device");


	sdev = kzalloc(sizeof(struct stub_device), GFP_KERNEL);
	if (!sdev)
		return NULL;

	sdev->udev = usb_get_dev(udev);


	sdev->devid		= (busnum << 16) | devnum;
	sdev->ud.side		= USBIP_STUB;
	sdev->ud.status		= SDEV_ST_AVAILABLE;
	spin_lock_init(&sdev->ud.lock);
	sdev->ud.tcp_socket	= NULL;

	INIT_LIST_HEAD(&sdev->priv_init);
	INIT_LIST_HEAD(&sdev->priv_tx);
	INIT_LIST_HEAD(&sdev->priv_free);
	INIT_LIST_HEAD(&sdev->unlink_free);
	INIT_LIST_HEAD(&sdev->unlink_tx);
	spin_lock_init(&sdev->priv_lock);

	init_waitqueue_head(&sdev->tx_waitq);

	sdev->ud.eh_ops.shutdown = stub_shutdown_connection;
	sdev->ud.eh_ops.reset    = stub_device_reset;
	sdev->ud.eh_ops.unusable = stub_device_unusable;

	usbip_start_eh(&sdev->ud);

	dev_dbg(&udev->dev, "register new device\n");

	return sdev;
}
