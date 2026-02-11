ch9200_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int retval = 0;
	unsigned char data[2];

	retval = usbnet_get_endpoints(dev, intf);
	if (retval)
		return retval;

	dev->mii.dev = dev->net;
	dev->mii.mdio_read = ch9200_mdio_read;
	dev->mii.mdio_write = ch9200_mdio_write;
	dev->mii.reg_num_mask = 0x1f;

	dev->mii.phy_id_mask = 0x1f;

	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->rx_urb_size = 24 * 64 + 16;
	mii_nway_restart(&dev->mii);

	data[0] = 0x01;
	data[1] = 0x0F;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_THRESHOLD, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0xA0;
	data[1] = 0x90;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_FIFO_DEPTH, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0x30;
	data[1] = 0x00;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_PAUSE, data,
			       0x02, CONTROL_TIMEOUT_MS);

	data[0] = 0x17;
	data[1] = 0xD8;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_FLOW_CONTROL,
			       data, 0x02, CONTROL_TIMEOUT_MS);


	data[0] = 0x01;
	data[1] = 0x00;
	retval = control_write(dev, REQUEST_WRITE, 0, 254, data, 0x02,
			       CONTROL_TIMEOUT_MS);

	data[0] = 0x5F;
	data[1] = 0x0D;
	retval = control_write(dev, REQUEST_WRITE, 0, MAC_REG_CTRL, data, 0x02,
			       CONTROL_TIMEOUT_MS);

	retval = get_mac_address(dev, dev->net->dev_addr);

	return retval;
}
