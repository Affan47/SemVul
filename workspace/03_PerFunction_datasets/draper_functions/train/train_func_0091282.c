usb_urb_reconfig(struct usb_data_stream *stream,
		struct usb_data_stream_properties *props)
{
	int buf_size;

	if (!props)
		return 0;


	if (props->type == USB_BULK) {
		buf_size = stream->props.u.bulk.buffersize;
	} else if (props->type == USB_ISOC) {
		buf_size = props->u.isoc.framesize * props->u.isoc.framesperurb;
	} else {
		dev_err(&stream->udev->dev, "%s: invalid endpoint type=%d\n",
				KBUILD_MODNAME, props->type);
		return -EINVAL;
	}

	if (stream->buf_num < props->count || stream->buf_size < buf_size) {
		dev_err(&stream->udev->dev,
				"%s: cannot reconfigure as allocated buffers are too small\n",
				KBUILD_MODNAME);
		return -EINVAL;
	}


	if (stream->props.type == props->type &&
			stream->props.count == props->count &&
			stream->props.endpoint == props->endpoint) {
		if (props->type == USB_BULK &&
				props->u.bulk.buffersize ==
				stream->props.u.bulk.buffersize)
			return 0;
		else if (props->type == USB_ISOC &&
				props->u.isoc.framesperurb ==
				stream->props.u.isoc.framesperurb &&
				props->u.isoc.framesize ==
				stream->props.u.isoc.framesize &&
				props->u.isoc.interval ==
				stream->props.u.isoc.interval)
			return 0;
	}

	dev_dbg(&stream->udev->dev, "%s: re-alloc urbs\n", __func__);

	usb_urb_free_urbs(stream);
	memcpy(&stream->props, props, sizeof(*props));
	if (props->type == USB_BULK)
		return usb_urb_alloc_bulk_urbs(stream);
	else if (props->type == USB_ISOC)
		return usb_urb_alloc_isoc_urbs(stream);

	return 0;
}
