reg_w_i(struct gspca_dev *gspca_dev,
			    u16 req,
			    u16 value,
			    u16 index)
{
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			req,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, NULL, 0,
			500);
	if (ret < 0) {
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	}
}
