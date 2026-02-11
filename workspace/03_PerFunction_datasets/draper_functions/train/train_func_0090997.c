lp3943_get_gpio_out_status(struct lp3943_gpio *lp3943_gpio,
				      struct gpio_chip *chip, unsigned offset)
{
	struct lp3943 *lp3943 = lp3943_gpio->lp3943;
	const struct lp3943_reg_cfg *mux = lp3943->mux_cfg;
	u8 read;
	int err;

	err = lp3943_read_byte(lp3943, mux[offset].reg, &read);
	if (err)
		return err;

	read = (read & mux[offset].mask) >> mux[offset].shift;

	if (read == LP3943_GPIO_OUT_HIGH)
		return 1;
	else if (read == LP3943_GPIO_OUT_LOW)
		return 0;
	else
		return -EINVAL;
}
