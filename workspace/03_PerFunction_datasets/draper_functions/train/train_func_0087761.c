read_tsi(struct da9034_touch *touch)
{
	uint8_t _x, _y, _v;
	int ret;

	ret = da903x_read(touch->da9034_dev, DA9034_TSI_X_MSB, &_x);
	if (ret)
		return ret;

	ret = da903x_read(touch->da9034_dev, DA9034_TSI_Y_MSB, &_y);
	if (ret)
		return ret;

	ret = da903x_read(touch->da9034_dev, DA9034_TSI_XY_LSB, &_v);
	if (ret)
		return ret;

	touch->last_x = ((_x << 2) & 0x3fc) | (_v & 0x3);
	touch->last_y = ((_y << 2) & 0x3fc) | ((_v & 0xc) >> 2);

	return 0;
}
