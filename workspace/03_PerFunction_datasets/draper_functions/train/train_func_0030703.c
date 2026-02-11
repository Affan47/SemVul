sierra_net_send_cmd(struct usbnet *dev,
		u8 *cmd, int cmdlen, const char * cmd_name)
{
	struct sierra_net_data *priv = sierra_net_get_private(dev);
	int  status;

	status = usbnet_write_cmd(dev, USB_CDC_SEND_ENCAPSULATED_COMMAND,
				  USB_DIR_OUT|USB_TYPE_CLASS|USB_RECIP_INTERFACE,
				  0, priv->ifnum, cmd, cmdlen);

	if (status != cmdlen && status != -ENODEV)
		netdev_err(dev->net, "Submit %s failed %d\n", cmd_name, status);

	return status;
}
