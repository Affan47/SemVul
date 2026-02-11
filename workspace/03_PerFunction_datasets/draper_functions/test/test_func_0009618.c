kaweth_async_set_rx_mode(struct kaweth_device *kaweth)
{
	int result;
	__u16 packet_filter_bitmap = kaweth->packet_filter_bitmap;

	kaweth->packet_filter_bitmap = 0;
	if (packet_filter_bitmap == 0)
		return;

	if (in_interrupt())
		return;

	result = kaweth_control(kaweth,
				usb_sndctrlpipe(kaweth->dev, 0),
				KAWETH_COMMAND_SET_PACKET_FILTER,
				USB_TYPE_VENDOR | USB_DIR_OUT | USB_RECIP_DEVICE,
				packet_filter_bitmap,
				0,
				(void *)&kaweth->scratch,
				0,
				KAWETH_CONTROL_TIMEOUT);

	if(result < 0) {
		dev_err(&kaweth->intf->dev, "Failed to set Rx mode: %d\n",
			result);
	}
	else {
		netdev_dbg(kaweth->net, "Set Rx mode to %d\n",
			   packet_filter_bitmap);
	}
}
