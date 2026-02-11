keypad_matrix_key_parse_dt(struct st_keyscan *keypad_data)
{
	struct device *dev = keypad_data->input_dev->dev.parent;
	struct device_node *np = dev->of_node;
	int error;

	error = matrix_keypad_parse_of_params(dev, &keypad_data->n_rows,
					      &keypad_data->n_cols);
	if (error) {
		dev_err(dev, "failed to parse keypad params\n");
		return error;
	}

	of_property_read_u32(np, "st,debounce-us", &keypad_data->debounce_us);

	dev_dbg(dev, "n_rows=%d n_col=%d debounce=%d\n",
		keypad_data->n_rows, keypad_data->n_cols,
		keypad_data->debounce_us);

	return 0;
}
