usblp_disconnect(struct usb_interface *intf)
{
	struct usblp *usblp = usb_get_intfdata(intf);

	usb_deregister_dev(intf, &usblp_class);

	if (!usblp || !usblp->dev) {
		dev_err(&intf->dev, "bogus disconnect\n");
		BUG();
	}

	device_remove_file(&intf->dev, &dev_attr_ieee1284_id);

	mutex_lock(&usblp_mutex);
	mutex_lock(&usblp->mut);
	usblp->present = 0;
	wake_up(&usblp->wwait);
	wake_up(&usblp->rwait);
	usb_set_intfdata(intf, NULL);

	usblp_unlink_urbs(usblp);
	mutex_unlock(&usblp->mut);

	if (!usblp->used)
		usblp_cleanup(usblp);
	mutex_unlock(&usblp_mutex);
}
