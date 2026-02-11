ad2s1210_initial(struct ad2s1210_state *st)
{
	unsigned char data;
	int ret;

	mutex_lock(&st->lock);
	if (st->pdata->gpioin)
		st->resolution = ad2s1210_read_resolution_pin(st);
	else
		ad2s1210_set_resolution_pin(st);

	ret = ad2s1210_config_write(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = AD2S1210_DEF_CONTROL & ~(AD2S1210_SET_RESOLUTION);
	data |= (st->resolution - 10) >> 1;
	ret = ad2s1210_config_write(st, data);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;

	if (ret & AD2S1210_MSB_IS_HIGH) {
		ret = -EIO;
		goto error_ret;
	}

	ret = ad2s1210_update_frequency_control_word(st);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_soft_reset(st);
error_ret:
	mutex_unlock(&st->lock);
	return ret;
}
