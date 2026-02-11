setvflip(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->flip_status)
		val = !val;
	sensor_write_mask(gspca_dev, 0x020, val ? 0x0001 : 0x0000 , 0x0001);
}
