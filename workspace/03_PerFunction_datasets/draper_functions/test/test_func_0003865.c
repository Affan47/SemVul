gpio_ir_recv_get_devtree_pdata(struct device *dev,
				  struct gpio_ir_recv_platform_data *pdata)
{
	struct device_node *np = dev->of_node;
	enum of_gpio_flags flags;
	int gpio;

	gpio = of_get_gpio_flags(np, 0, &flags);
	if (gpio < 0) {
		if (gpio != -EPROBE_DEFER)
			dev_err(dev, "Failed to get gpio flags (%d)\n", gpio);
		return gpio;
	}

	pdata->gpio_nr = gpio;
	pdata->active_low = (flags & OF_GPIO_ACTIVE_LOW);

	pdata->map_name = of_get_property(np, "linux,rc-map-name", NULL);
	pdata->allowed_protos = 0;

	return 0;
}
