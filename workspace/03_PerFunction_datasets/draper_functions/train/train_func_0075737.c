mdc800_usb_disconnect (struct usb_interface *intf)
{
	struct mdc800_data* mdc800 = usb_get_intfdata(intf);

	dev_dbg(&intf->dev, "(%s) called\n", __func__);

	if (mdc800) {
		if (mdc800->state == NOT_CONNECTED)
			return;

		usb_deregister_dev(intf, &mdc800_class);


		mutex_lock(&mdc800->io_lock);
		mdc800->state=NOT_CONNECTED;

		usb_kill_urb(mdc800->irq_urb);
		usb_kill_urb(mdc800->write_urb);
		usb_kill_urb(mdc800->download_urb);
		mutex_unlock(&mdc800->io_lock);

		mdc800->dev = NULL;
		usb_set_intfdata(intf, NULL);
	}
	dev_info(&intf->dev, "Mustek MDC800 disconnected from USB.\n");
}
