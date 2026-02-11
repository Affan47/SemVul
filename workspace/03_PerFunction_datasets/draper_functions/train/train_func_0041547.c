vp702x_usb_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct dvb_usb_device *d;
	struct vp702x_device_state *st;
	int ret;

	ret = dvb_usb_device_init(intf, &vp702x_properties,
				   THIS_MODULE, &d, adapter_nr);
	if (ret)
		goto out;

	st = d->priv;
	st->buf_len = 16;
	st->buf = kmalloc(st->buf_len, GFP_KERNEL);
	if (!st->buf) {
		ret = -ENOMEM;
		dvb_usb_device_exit(intf);
		goto out;
	}
	mutex_init(&st->buf_mutex);

out:
	return ret;

}
