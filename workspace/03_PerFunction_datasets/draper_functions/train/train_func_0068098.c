st5481_setup_in(struct st5481_in *in)
{
	struct usb_device *dev = in->adapter->usb_dev;
	int retval;

	DBG(4, "");

	in->rcvbuf = kmalloc(in->bufsize, GFP_KERNEL);
	retval = -ENOMEM;
	if (!in->rcvbuf)
		goto err;

	retval = st5481_setup_isocpipes(in->urb, dev,
					usb_rcvisocpipe(dev, in->ep),
					in->num_packets,  in->packet_size,
					in->num_packets * in->packet_size,
					usb_in_complete, in);
	if (retval)
		goto err_free;
	return 0;

err_free:
	kfree(in->rcvbuf);
err:
	return retval;
}
