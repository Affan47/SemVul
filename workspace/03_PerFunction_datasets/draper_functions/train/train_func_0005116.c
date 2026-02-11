asix_read_cmd(struct usbnet *dev, u8 cmd, u16 value, u16 index,
		  u16 size, void *data)
{
	int ret;
	ret = usbnet_read_cmd(dev, cmd,
			       USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       value, index, data, size);

	if (ret != size && ret >= 0)
		return -EINVAL;
	return ret;
}
