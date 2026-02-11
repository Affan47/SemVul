mdio_mux_gpio_probe(struct platform_device *pdev)
{
	struct mdio_mux_gpio_state *s;
	int r;

	s = devm_kzalloc(&pdev->dev, sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	s->gpios = gpiod_get_array(&pdev->dev, NULL, GPIOD_OUT_LOW);
	if (IS_ERR(s->gpios))
		return PTR_ERR(s->gpios);

	r = mdio_mux_init(&pdev->dev,
			  mdio_mux_gpio_switch_fn, &s->mux_handle, s);

	if (r != 0) {
		gpiod_put_array(s->gpios);
		return r;
	}

	pdev->dev.platform_data = s;
	return 0;
}
