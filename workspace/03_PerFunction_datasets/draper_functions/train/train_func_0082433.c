sensor_write_regs(struct gspca_dev *gspca_dev,
	const struct sensor_w_data *data, int len)
{
	int i, rc;

	for (i = 0; i < len; i++) {
		rc = sensor_write_reg(gspca_dev, data[i].reg, data[i].flags,
					  data[i].data, data[i].len);
		if (rc < 0)
			return rc;
	}

	return 0;
}
