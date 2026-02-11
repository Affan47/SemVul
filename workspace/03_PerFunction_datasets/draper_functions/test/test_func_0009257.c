i2c_w(struct gspca_dev *gspca_dev, const u8 *buf)
{
	int retry = 60;

	if (gspca_dev->usb_err < 0)
		return;


	reg_w(gspca_dev, 0x08, buf, 8);
	while (retry--) {
		if (gspca_dev->usb_err < 0)
			return;
		msleep(1);
		reg_r(gspca_dev, 0x08);
		if (gspca_dev->usb_buf[0] & 0x04) {
			if (gspca_dev->usb_buf[0] & 0x08) {
				dev_err(gspca_dev->v4l2_dev.dev,
					"i2c error writing %8ph\n", buf);
				gspca_dev->usb_err = -EIO;
			}
			return;
		}
	}

	dev_err(gspca_dev->v4l2_dev.dev, "i2c write timeout\n");
	gspca_dev->usb_err = -EIO;
}
