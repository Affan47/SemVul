kvaser_usbcan_rx_error(const struct kvaser_usb *dev,
				   const struct kvaser_msg *msg)
{
	struct kvaser_usb_error_summary es = { };

	switch (msg->id) {

	case CMD_CHIP_STATE_EVENT:
		es.channel = msg->u.usbcan.chip_state_event.channel;
		es.status =  msg->u.usbcan.chip_state_event.status;
		es.txerr = msg->u.usbcan.chip_state_event.tx_errors_count;
		es.rxerr = msg->u.usbcan.chip_state_event.rx_errors_count;
		kvaser_usbcan_conditionally_rx_error(dev, &es);
		break;

	case CMD_CAN_ERROR_EVENT:
		es.channel = 0;
		es.status = msg->u.usbcan.error_event.status_ch0;
		es.txerr = msg->u.usbcan.error_event.tx_errors_count_ch0;
		es.rxerr = msg->u.usbcan.error_event.rx_errors_count_ch0;
		es.usbcan.other_ch_status =
			msg->u.usbcan.error_event.status_ch1;
		kvaser_usbcan_conditionally_rx_error(dev, &es);


		if (dev->nchannels == MAX_USBCAN_NET_DEVICES) {
			es.channel = 1;
			es.status = msg->u.usbcan.error_event.status_ch1;
			es.txerr = msg->u.usbcan.error_event.tx_errors_count_ch1;
			es.rxerr = msg->u.usbcan.error_event.rx_errors_count_ch1;
			es.usbcan.other_ch_status =
				msg->u.usbcan.error_event.status_ch0;
			kvaser_usbcan_conditionally_rx_error(dev, &es);
		}
		break;

	default:
		dev_err(dev->udev->dev.parent, "Invalid msg id (%d)\n",
			msg->id);
	}
}
