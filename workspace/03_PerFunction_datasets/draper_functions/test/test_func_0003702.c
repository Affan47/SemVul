elan_setup_input_device(struct elan_tp_data *data)
{
	struct device *dev = &data->client->dev;
	struct input_dev *input;
	unsigned int max_width = max(data->width_x, data->width_y);
	unsigned int min_width = min(data->width_x, data->width_y);
	int error;

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	input->name = "Elan Touchpad";
	input->id.bustype = BUS_I2C;
	input->id.vendor = ELAN_VENDOR_ID;
	input->id.product = data->product_id;
	input_set_drvdata(input, data);

	error = input_mt_init_slots(input, ETP_MAX_FINGERS,
				    INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED);
	if (error) {
		dev_err(dev, "failed to initialize MT slots: %d\n", error);
		return error;
	}

	__set_bit(EV_ABS, input->evbit);
	__set_bit(INPUT_PROP_POINTER, input->propbit);
	__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);
	__set_bit(BTN_LEFT, input->keybit);


	input_set_abs_params(input, ABS_X, 0, data->max_x, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, data->max_y, 0, 0);
	input_abs_set_res(input, ABS_X, data->x_res);
	input_abs_set_res(input, ABS_Y, data->y_res);
	input_set_abs_params(input, ABS_PRESSURE, 0, ETP_MAX_PRESSURE, 0, 0);
	input_set_abs_params(input, ABS_TOOL_WIDTH, 0, ETP_FINGER_WIDTH, 0, 0);
	input_set_abs_params(input, ABS_DISTANCE, 0, 1, 0, 0);


	input_set_abs_params(input, ABS_MT_POSITION_X, 0, data->max_x, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, data->max_y, 0, 0);
	input_abs_set_res(input, ABS_MT_POSITION_X, data->x_res);
	input_abs_set_res(input, ABS_MT_POSITION_Y, data->y_res);
	input_set_abs_params(input, ABS_MT_PRESSURE, 0,
			     ETP_MAX_PRESSURE, 0, 0);
	input_set_abs_params(input, ABS_MT_TOUCH_MAJOR, 0,
			     ETP_FINGER_WIDTH * max_width, 0, 0);
	input_set_abs_params(input, ABS_MT_TOUCH_MINOR, 0,
			     ETP_FINGER_WIDTH * min_width, 0, 0);

	data->input = input;

	return 0;
}
