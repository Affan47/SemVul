bq2415x_get_current_limit(struct bq2415x_device *bq)
{
	int ret;

	ret = bq2415x_i2c_read_mask(bq, BQ2415X_REG_CONTROL,
			BQ2415X_MASK_LIMIT, BQ2415X_SHIFT_LIMIT);
	if (ret < 0)
		return ret;
	else if (ret == 0)
		return 100;
	else if (ret == 1)
		return 500;
	else if (ret == 2)
		return 800;
	else if (ret == 3)
		return 1800;
	return -EINVAL;
}
