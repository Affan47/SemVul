bma150_soft_reset(struct bma150_data *bma150)
{
	int error;

	error = bma150_set_reg_bits(bma150->client, 1, BMA150_SW_RES_POS,
				BMA150_SW_RES_MSK, BMA150_SW_RES_REG);
	if (error)
		return error;

	msleep(2);
	return 0;
}
