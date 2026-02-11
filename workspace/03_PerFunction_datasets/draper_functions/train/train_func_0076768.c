recv_control_msg(struct pwc_device *pdev,
	u8 request, u16 value, int recv_count)
{
	int rc;

	rc = usb_control_msg(pdev->udev, usb_rcvctrlpipe(pdev->udev, 0),
		request,
		USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		value, pdev->vcinterface,
		pdev->ctrl_buf, recv_count, USB_CTRL_GET_TIMEOUT);
	if (rc < 0)
		PWC_ERROR("recv_control_msg error %d req %02x val %04x\n",
			  rc, request, value);
	return rc;
}
