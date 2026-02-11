esd_usb2_read_bulk_callback(struct urb *urb)
{
	struct esd_usb2 *dev = urb->context;
	int retval;
	int pos = 0;
	int i;

	switch (urb->status) {
	case 0:
		break;

	case -ENOENT:
	case -EPIPE:
	case -EPROTO:
	case -ESHUTDOWN:
		return;

	default:
		dev_info(dev->udev->dev.parent,
			 "Rx URB aborted (%d)\n", urb->status);
		goto resubmit_urb;
	}

	while (pos < urb->actual_length) {
		struct esd_usb2_msg *msg;

		msg = (struct esd_usb2_msg *)(urb->transfer_buffer + pos);

		switch (msg->msg.hdr.cmd) {
		case CMD_CAN_RX:
			if (msg->msg.rx.net >= dev->net_count) {
				dev_err(dev->udev->dev.parent, "format error\n");
				break;
			}

			esd_usb2_rx_can_msg(dev->nets[msg->msg.rx.net], msg);
			break;

		case CMD_CAN_TX:
			if (msg->msg.txdone.net >= dev->net_count) {
				dev_err(dev->udev->dev.parent, "format error\n");
				break;
			}

			esd_usb2_tx_done_msg(dev->nets[msg->msg.txdone.net],
					     msg);
			break;
		}

		pos += msg->msg.hdr.len << 2;

		if (pos > urb->actual_length) {
			dev_err(dev->udev->dev.parent, "format error\n");
			break;
		}
	}

resubmit_urb:
	usb_fill_bulk_urb(urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
			  urb->transfer_buffer, RX_BUFFER_SIZE,
			  esd_usb2_read_bulk_callback, dev);

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval == -ENODEV) {
		for (i = 0; i < dev->net_count; i++) {
			if (dev->nets[i])
				netif_device_detach(dev->nets[i]->netdev);
		}
	} else if (retval) {
		dev_err(dev->udev->dev.parent,
			"failed resubmitting read bulk urb: %d\n", retval);
	}

	return;
}
