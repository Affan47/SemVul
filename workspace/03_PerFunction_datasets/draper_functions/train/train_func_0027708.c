ad5593r_gpio_read(struct ad5592r_state *st, u8 *value)
{
	int ret;

	ret = ad5592r_reg_write(st, AD5592R_REG_GPIO_IN_EN,
				AD5592R_GPIO_READBACK_EN | st->gpio_in);
	if (ret)
		return ret;

	ret = ad5592r_spi_wnop_r16(st, &st->spi_msg);
	if (ret)
		return ret;

	*value = (u8) be16_to_cpu(st->spi_msg);

	return 0;
}
