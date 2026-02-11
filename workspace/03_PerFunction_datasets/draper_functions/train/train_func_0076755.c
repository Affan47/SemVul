brcmf_usb_send_ctl(struct brcmf_usbdev_info *devinfo, u8 *buf, int len)
{
	int ret;
	u16 size;

	brcmf_dbg(USB, "Enter\n");
	if (devinfo == NULL || buf == NULL ||
	    len == 0 || devinfo->ctl_urb == NULL)
		return -EINVAL;

	size = len;
	devinfo->ctl_write.wLength = cpu_to_le16p(&size);
	devinfo->ctl_urb->transfer_buffer_length = size;
	devinfo->ctl_urb_status = 0;
	devinfo->ctl_urb_actual_length = 0;

	usb_fill_control_urb(devinfo->ctl_urb,
		devinfo->usbdev,
		devinfo->ctl_out_pipe,
		(unsigned char *) &devinfo->ctl_write,
		buf, size,
		(usb_complete_t)brcmf_usb_ctlwrite_complete,
		devinfo);

	ret = usb_submit_urb(devinfo->ctl_urb, GFP_ATOMIC);
	if (ret < 0)
		brcmf_err("usb_submit_urb failed %d\n", ret);

	return ret;
}
