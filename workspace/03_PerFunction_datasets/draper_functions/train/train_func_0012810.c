mt9m111_set_hvflip(struct gspca_dev *gspca_dev)
{
	int err;
	u8 data[2] = {0x00, 0x00};
	struct sd *sd = (struct sd *) gspca_dev;
	int hflip;
	int vflip;

	PDEBUG(D_CONF, "Set hvflip to %d %d", sd->hflip->val, sd->vflip->val);


	hflip = !sd->hflip->val;
	vflip = !sd->vflip->val;


	err = m5602_write_sensor(sd, MT9M111_PAGE_MAP, data, 2);
	if (err < 0)
		return err;

	data[0] = MT9M111_RMB_OVER_SIZED;
	if (gspca_dev->pixfmt.width == 640) {
		data[1] = MT9M111_RMB_ROW_SKIP_2X |
			  MT9M111_RMB_COLUMN_SKIP_2X |
			  (hflip << 1) | vflip;
	} else {
		data[1] = MT9M111_RMB_ROW_SKIP_4X |
			  MT9M111_RMB_COLUMN_SKIP_4X |
			  (hflip << 1) | vflip;
	}
	err = m5602_write_sensor(sd, MT9M111_SC_R_MODE_CONTEXT_B,
					data, 2);
	return err;
}
