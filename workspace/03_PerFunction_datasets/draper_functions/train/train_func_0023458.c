gpiod_get_index(struct device *dev,
					       const char *con_id,
					       unsigned int idx,
					       enum gpiod_flags flags)
{
	struct gpio_desc *desc = NULL;
	int status;
	enum gpio_lookup_flags lookupflags = 0;

	dev_dbg(dev, "GPIO lookup for consumer %s\n", con_id);

	if (dev) {

		if (IS_ENABLED(CONFIG_OF) && dev->of_node) {
			dev_dbg(dev, "using device tree for GPIO lookup\n");
			desc = of_find_gpio(dev, con_id, idx, &lookupflags);
		} else if (ACPI_COMPANION(dev)) {
			dev_dbg(dev, "using ACPI for GPIO lookup\n");
			desc = acpi_find_gpio(dev, con_id, idx, &lookupflags);
		}
	}


	if (!desc || desc == ERR_PTR(-ENOENT)) {
		dev_dbg(dev, "using lookup tables for GPIO lookup\n");
		desc = gpiod_find(dev, con_id, idx, &lookupflags);
	}

	if (IS_ERR(desc)) {
		dev_dbg(dev, "lookup for GPIO %s failed\n", con_id);
		return desc;
	}

	status = gpiod_request(desc, con_id);
	if (status < 0)
		return ERR_PTR(status);

	status = gpiod_configure_flags(desc, con_id, lookupflags, flags);
	if (status < 0) {
		dev_dbg(dev, "setup of GPIO %s failed\n", con_id);
		gpiod_put(desc);
		return ERR_PTR(status);
	}

	return desc;
}
