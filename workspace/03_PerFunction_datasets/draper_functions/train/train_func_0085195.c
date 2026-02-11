setframerate(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 fr_idx;

	fr_idx = get_fr_idx(gspca_dev);

	if (sd->bridge == BRIDGE_TP6810) {
		reg_r(gspca_dev, 0x7b);
		reg_w(gspca_dev, 0x7b,
			sd->sensor == SENSOR_CX0342 ? 0x10 : 0x90);
		if (val >= 128)
			fr_idx = 0xf0;
	}

	reg_w(gspca_dev, TP6800_R3F_FRAME_RATE, fr_idx);

	if (sd->sensor == SENSOR_CX0342)
		i2c_w(gspca_dev, CX0342_AUTO_ADC_CALIB, 0x01);
}
