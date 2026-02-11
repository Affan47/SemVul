s5c73m3_configure_gpios(struct s5c73m3 *state)
{
	static const char * const gpio_names[] = {
		"S5C73M3_STBY", "S5C73M3_RST"
	};
	struct i2c_client *c = state->i2c_client;
	struct s5c73m3_gpio *g = state->gpio;
	int ret, i;

	for (i = 0; i < GPIO_NUM; ++i) {
		unsigned int flags = GPIOF_DIR_OUT;
		if (g[i].level)
			flags |= GPIOF_INIT_HIGH;
		ret = devm_gpio_request_one(&c->dev, g[i].gpio, flags,
					    gpio_names[i]);
		if (ret) {
			v4l2_err(c, "failed to request gpio %s\n",
				 gpio_names[i]);
			return ret;
		}
	}
	return 0;
}
