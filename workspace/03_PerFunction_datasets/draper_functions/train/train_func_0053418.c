setexposure(struct gspca_dev *gspca_dev)
{
	u8 clockdiv;
	u16 exposure;


	clockdiv = (90 * gspca_dev->exposure->val + 1999) / 2000;


	if (clockdiv < 6)
		clockdiv = 6;
	else if (clockdiv > 63)
		clockdiv = 63;


	if (clockdiv < 6 || clockdiv > 12)
		clockdiv = ((clockdiv + 2) / 3) * 3;


	exposure = (gspca_dev->exposure->val * 45 * 448) / (1000 * clockdiv);

	exposure = 448 - exposure;

	reg_w(gspca_dev, 0xff, 0x03);
	reg_w(gspca_dev, 0x02, clockdiv);
	reg_w(gspca_dev, 0x0e, exposure & 0xff);
	reg_w(gspca_dev, 0x0f, exposure >> 8);


	reg_w(gspca_dev, 0x11, 0x01);
}
