bcm203x_complete(struct urb *urb)
{
	struct bcm203x_data *data = urb->context;
	struct usb_device *udev = urb->dev;
	int len;

	BT_DBG("udev %p urb %p", udev, urb);

	if (urb->status) {
		BT_ERR("URB failed with status %d", urb->status);
		data->state = BCM203X_ERROR;
		return;
	}

	switch (data->state) {
	case BCM203X_LOAD_MINIDRV:
		memcpy(data->buffer, "#", 1);

		usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, BCM203X_OUT_EP),
				data->buffer, 1, bcm203x_complete, data);

		data->state = BCM203X_SELECT_MEMORY;


		schedule_work(&data->work);
		break;

	case BCM203X_SELECT_MEMORY:
		usb_fill_int_urb(urb, udev, usb_rcvintpipe(udev, BCM203X_IN_EP),
				data->buffer, 32, bcm203x_complete, data, 1);

		data->state = BCM203X_CHECK_MEMORY;

		if (usb_submit_urb(data->urb, GFP_ATOMIC) < 0)
			BT_ERR("Can't submit URB");
		break;

	case BCM203X_CHECK_MEMORY:
		if (data->buffer[0] != '#') {
			BT_ERR("Memory select failed");
			data->state = BCM203X_ERROR;
			break;
		}

		data->state = BCM203X_LOAD_FIRMWARE;

	case BCM203X_LOAD_FIRMWARE:
		if (data->fw_sent == data->fw_size) {
			usb_fill_int_urb(urb, udev, usb_rcvintpipe(udev, BCM203X_IN_EP),
				data->buffer, 32, bcm203x_complete, data, 1);

			data->state = BCM203X_CHECK_FIRMWARE;
		} else {
			len = min_t(uint, data->fw_size - data->fw_sent, 4096);

			usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, BCM203X_OUT_EP),
				data->fw_data + data->fw_sent, len, bcm203x_complete, data);

			data->fw_sent += len;
		}

		if (usb_submit_urb(data->urb, GFP_ATOMIC) < 0)
			BT_ERR("Can't submit URB");
		break;

	case BCM203X_CHECK_FIRMWARE:
		if (data->buffer[0] != '.') {
			BT_ERR("Firmware loading failed");
			data->state = BCM203X_ERROR;
			break;
		}

		data->state = BCM203X_RESET;
		break;
	}
}
