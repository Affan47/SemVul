setautogain(struct gspca_dev *gspca_dev, s32 autogain)
{
	u8 val;


	val = sccb_read(gspca_dev, 0x13);
	sccb_write(gspca_dev, 0xff, 0x00);
	if (autogain)
		val |= 0x05;
	else
		val &= 0xfa;
	sccb_write(gspca_dev, 0x13, val);
}
