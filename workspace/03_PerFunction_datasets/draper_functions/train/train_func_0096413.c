synusb_post_reset(struct usb_interface *intf)
{
	struct synusb *synusb = usb_get_intfdata(intf);
	struct input_dev *input_dev = synusb->input;
	int retval = 0;

	if ((input_dev->users || (synusb->flags & SYNUSB_IO_ALWAYS)) &&
	    usb_submit_urb(synusb->urb, GFP_NOIO) < 0) {
		retval = -EIO;
	}

	mutex_unlock(&input_dev->mutex);

	return retval;
}
