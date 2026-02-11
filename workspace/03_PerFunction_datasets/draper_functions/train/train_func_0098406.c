lan78xx_disconnect(struct usb_interface *intf)
{
	struct lan78xx_net		*dev;
	struct usb_device		*udev;
	struct net_device		*net;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);
	if (!dev)
		return;

	udev = interface_to_usbdev(intf);

	net = dev->net;
	unregister_netdev(net);

	cancel_delayed_work_sync(&dev->wq);

	usb_scuttle_anchored_urbs(&dev->deferred);

	lan78xx_unbind(dev, intf);

	usb_kill_urb(dev->urb_intr);
	usb_free_urb(dev->urb_intr);

	free_netdev(net);
	usb_put_dev(udev);
}
