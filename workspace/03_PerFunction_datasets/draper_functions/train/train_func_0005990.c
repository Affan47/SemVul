usb_ftdi_elan_read_pcimem(struct platform_device *pdev, int mem_offset,
			      u8 width, u32 *data)
{
	struct usb_ftdi *ftdi = platform_device_to_usb_ftdi(pdev);
	if (ftdi->initialized == 0) {
		return -ENODEV;
	} else
		return ftdi_elan_read_pcimem(ftdi, mem_offset, width, data);
}
