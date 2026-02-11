mmc35240_init(struct mmc35240_data *data)
{
	int ret, y_convert, z_convert;
	unsigned int reg_id;
	u8 otp_data[6];

	ret = regmap_read(data->regmap, MMC35240_REG_ID, &reg_id);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading product id\n");
		return ret;
	}

	dev_dbg(&data->client->dev, "MMC35240 chip id %x\n", reg_id);


	ret = mmc35240_hw_set(data, true);
	if (ret < 0)
		return ret;
	usleep_range(MMC53240_WAIT_SET_RESET, MMC53240_WAIT_SET_RESET + 1);

	ret = mmc35240_hw_set(data, false);
	if (ret < 0)
		return ret;


	ret = regmap_update_bits(data->regmap, MMC35240_REG_CTRL1,
				 MMC35240_CTRL1_BW_MASK,
				 data->res << MMC35240_CTRL1_BW_SHIFT);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_read(data->regmap, MMC35240_OTP_START_ADDR,
			       (u8 *)otp_data, sizeof(otp_data));
	if (ret < 0)
		return ret;

	y_convert = MMC35240_OTP_CONVERT_Y(((otp_data[1] & 0x03) << 4) |
					   (otp_data[2] >> 4));
	z_convert = MMC35240_OTP_CONVERT_Z(otp_data[3] & 0x3f);

	data->axis_coef[0] = MMC35240_X_COEFF(1);
	data->axis_coef[1] = MMC35240_Y_COEFF(y_convert);
	data->axis_coef[2] = MMC35240_Z_COEFF(z_convert);

	data->axis_scale[0] = 1;
	data->axis_scale[1] = 1000;
	data->axis_scale[2] = 10000;

	return 0;
}
