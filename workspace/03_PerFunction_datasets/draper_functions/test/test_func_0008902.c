af9013_power_ctrl(struct af9013_state *state, u8 onoff)
{
	int ret, i;
	u8 tmp;

	dev_dbg(&state->i2c->dev, "%s: onoff=%d\n", __func__, onoff);


	ret = af9013_wr_reg_bits(state, 0xd417, 4, 1, 1);
	if (ret)
		goto err;


	ret = af9013_wr_reg(state, 0xaeff, 1);
	if (ret)
		goto err;


	for (i = 0; i < 150; i++) {
		ret = af9013_rd_reg_bits(state, 0xd417, 1, 1, &tmp);
		if (ret)
			goto err;

		if (tmp)
			break;

		usleep_range(5000, 25000);
	}

	if (!tmp)
		return -ETIMEDOUT;

	if (onoff) {

		ret = af9013_wr_reg_bits(state, 0xd417, 1, 1, 0);
		if (ret)
			goto err;


		ret = af9013_wr_reg_bits(state, 0xd417, 4, 1, 0);


		ret = af9013_wr_reg_bits(state, 0xd73a, 3, 1, 0);
	} else {

		ret = af9013_wr_reg_bits(state, 0xd73a, 3, 1, 1);
	}

	return ret;
err:
	dev_dbg(&state->i2c->dev, "%s: failed=%d\n", __func__, ret);
	return ret;
}
