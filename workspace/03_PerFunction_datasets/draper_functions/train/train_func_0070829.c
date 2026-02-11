send_midi_async(struct usb_line6 *line6, unsigned char *data,
			   int length)
{
	struct urb *urb;
	int retval;
	unsigned char *transfer_buffer;

	urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (urb == NULL)
		return -ENOMEM;

	transfer_buffer = kmemdup(data, length, GFP_ATOMIC);

	if (transfer_buffer == NULL) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	usb_fill_int_urb(urb, line6->usbdev,
			 usb_sndbulkpipe(line6->usbdev,
					 line6->properties->ep_ctrl_w),
			 transfer_buffer, length, midi_sent, line6,
			 line6->interval);
	urb->actual_length = 0;
	retval = usb_submit_urb(urb, GFP_ATOMIC);

	if (retval < 0) {
		dev_err(line6->ifcdev, "usb_submit_urb failed\n");
		usb_free_urb(urb);
		return retval;
	}

	++line6->line6midi->num_active_send_urbs;
	return 0;
}
