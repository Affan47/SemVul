m5602_start_transfer(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 *buf = sd->gspca_dev.usb_buf;
	int err;


	const u8 buffer[4] = {0x13, 0xf9, 0x0f, 0x01};

	if (sd->sensor->start)
		sd->sensor->start(sd);

	memcpy(buf, buffer, sizeof(buffer));
	err = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      0x04, 0x40, 0x19, 0x0000, buf,
			      sizeof(buffer), M5602_URB_MSG_TIMEOUT);

	PDEBUG(D_STREAM, "Transfer started");
	return (err < 0) ? err : 0;
}
