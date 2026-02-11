matrix_keypad_parse_of_params(struct device *dev,
				  unsigned int *rows, unsigned int *cols)
{
	struct device_node *np = dev->of_node;

	if (!np) {
		dev_err(dev, "missing DT data");
		return -EINVAL;
	}
	of_property_read_u32(np, "keypad,num-rows", rows);
	of_property_read_u32(np, "keypad,num-columns", cols);
	if (!*rows || !*cols) {
		dev_err(dev, "number of keypad rows/columns not specified\n");
		return -EINVAL;
	}

	return 0;
}
