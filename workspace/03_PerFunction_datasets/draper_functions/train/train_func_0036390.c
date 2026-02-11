kaweth_disconnect(struct usb_interface *intf)
{
	struct kaweth_device *kaweth = usb_get_intfdata(intf);
	struct net_device *netdev;

	dev_info(&intf->dev, "Unregistering\n");

	usb_set_intfdata(intf, NULL);
	if (!kaweth) {
		dev_warn(&intf->dev, "unregistering non-existent device\n");
		return;
	}
	netdev = kaweth->net;

	netdev_dbg(kaweth->net, "Unregistering net device\n");
	unregister_netdev(netdev);

	usb_free_urb(kaweth->rx_urb);
	usb_free_urb(kaweth->tx_urb);
	usb_free_urb(kaweth->irq_urb);

	usb_free_coherent(kaweth->dev, KAWETH_BUF_SIZE, (void *)kaweth->rx_buf, kaweth->rxbufferhandle);
	usb_free_coherent(kaweth->dev, INTBUFFERSIZE, (void *)kaweth->intbuffer, kaweth->intbufferhandle);

	free_netdev(netdev);
}
