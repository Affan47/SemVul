reg_w(struct gspca_dev *gspca_dev, u16 value, u16 index)
{
	char buff[1];
	int rc;

	PDEBUG(D_USBO,
		"reg_w bReq=0x0B, bReqT=0xC0, wVal=0x%04X, wInd=0x%04X\n",
		value, index);
	rc = usb_control_msg(gspca_dev->dev, usb_rcvctrlpipe(gspca_dev->dev, 0),
		0x0B, 0xC0, value, index, buff, 1, 500);
	PDEBUG(D_USBO, "rc=%d, ret={0x%02X}", rc, buff[0]);
	if (rc < 0) {
		PERR("Failed reg_w(0x0B, 0xC0, 0x%04X, 0x%04X) w/ rc %d\n",
			value, index, rc);
		gspca_dev->usb_err = rc;
		return;
	}
	if (val_reply(gspca_dev, buff, rc)) {
		PERR("Bad reply to reg_w(0x0B, 0xC0, 0x%04X, 0x%04X\n",
			value, index);
		gspca_dev->usb_err = -EIO;
	}
}
