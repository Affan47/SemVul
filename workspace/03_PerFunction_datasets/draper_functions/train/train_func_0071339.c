of_clk_gpio_delayed_register_get(
		struct of_phandle_args *clkspec, void *_data)
{
	struct clk_gpio_delayed_register_data *data = _data;
	struct clk *clk;
	int gpio;
	enum of_gpio_flags of_flags;

	mutex_lock(&data->lock);

	if (data->clk) {
		mutex_unlock(&data->lock);
		return data->clk;
	}

	gpio = of_get_named_gpio_flags(data->node, data->gpio_name, 0,
			&of_flags);
	if (gpio < 0) {
		mutex_unlock(&data->lock);
		if (gpio == -EPROBE_DEFER)
			pr_debug("%s: %s: GPIOs not yet available, retry later\n",
					data->node->name, __func__);
		else
			pr_err("%s: %s: Can't get '%s' DT property\n",
					data->node->name, __func__,
					data->gpio_name);
		return ERR_PTR(gpio);
	}

	clk = data->clk_register_get(data->node->name, data->parent_names,
			data->num_parents, gpio, of_flags & OF_GPIO_ACTIVE_LOW);
	if (IS_ERR(clk))
		goto out;

	data->clk = clk;
out:
	mutex_unlock(&data->lock);

	return clk;
}
