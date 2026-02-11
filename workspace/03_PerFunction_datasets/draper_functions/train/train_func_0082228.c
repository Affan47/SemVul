m5602_write_bridge(struct sd *sd, const u8 address, const u8 i2c_data)
{
	int err;
	struct gspca_dev *gspca_dev = (struct gspca_dev *) sd;
	struct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	PDEBUG(D_CONF, "Writing bridge register 0x%x with 0x%x",
	       address, i2c_data);

	memcpy(buf, bridge_urb_skeleton,
	       sizeof(bridge_urb_skeleton));
	buf[1] = address;
	buf[3] = i2c_data;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				0x04, 0x40, 0x19,
				0x0000, buf,
				4, M5602_URB_MSG_TIMEOUT);


	return (err < 0) ? err : 0;
}
