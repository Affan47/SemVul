vendor_command(struct cypress *dev, unsigned char request,
			  unsigned char address, unsigned char data)
{
	int retval = 0;
	unsigned int pipe;
	unsigned char *iobuf;


	iobuf = kzalloc(CYPRESS_MAX_REQSIZE, GFP_KERNEL);
	if (!iobuf) {
		dev_err(&dev->udev->dev, "Out of memory!\n");
		retval = -ENOMEM;
		goto error;
	}

	dev_dbg(&dev->udev->dev, "Sending usb_control_msg (data: %d)\n", data);


	pipe = usb_rcvctrlpipe(dev->udev, 0);
	retval = usb_control_msg(dev->udev, pipe, request,
				 USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				 address, data, iobuf, CYPRESS_MAX_REQSIZE,
				 USB_CTRL_GET_TIMEOUT);


	switch (request) {
		case CYPRESS_READ_PORT:
			if (address == CYPRESS_READ_PORT_ID0) {
				dev->port[0] = iobuf[1];
				dev_dbg(&dev->udev->dev,
					"READ_PORT0 returned: %d\n",
					dev->port[0]);
			}
			else if (address == CYPRESS_READ_PORT_ID1) {
				dev->port[1] = iobuf[1];
				dev_dbg(&dev->udev->dev,
					"READ_PORT1 returned: %d\n",
					dev->port[1]);
			}
			break;
	}

	kfree(iobuf);
error:
	return retval;
}
