icn8318_irq(int irq, void *dev_id)
{
	struct icn8318_data *data = dev_id;
	struct device *dev = &data->client->dev;
	struct icn8318_touch_data touch_data;
	int i, ret, x, y;

	ret = icn8318_read_touch_data(data->client, &touch_data);
	if (ret < 0) {
		dev_err(dev, "Error reading touch data: %d\n", ret);
		return IRQ_HANDLED;
	}

	if (touch_data.softbutton) {


		return IRQ_HANDLED;
	}

	if (touch_data.touch_count > ICN8318_MAX_TOUCHES) {
		dev_warn(dev, "Too much touches %d > %d\n",
			 touch_data.touch_count, ICN8318_MAX_TOUCHES);
		touch_data.touch_count = ICN8318_MAX_TOUCHES;
	}

	for (i = 0; i < touch_data.touch_count; i++) {
		struct icn8318_touch *touch = &touch_data.touches[i];
		bool act = icn8318_touch_active(touch->event);

		input_mt_slot(data->input, touch->slot);
		input_mt_report_slot_state(data->input, MT_TOOL_FINGER, act);
		if (!act)
			continue;

		x = be16_to_cpu(touch->x);
		y = be16_to_cpu(touch->y);

		if (data->invert_x)
			x = data->max_x - x;

		if (data->invert_y)
			y = data->max_y - y;

		if (!data->swap_x_y) {
			input_event(data->input, EV_ABS, ABS_MT_POSITION_X, x);
			input_event(data->input, EV_ABS, ABS_MT_POSITION_Y, y);
		} else {
			input_event(data->input, EV_ABS, ABS_MT_POSITION_X, y);
			input_event(data->input, EV_ABS, ABS_MT_POSITION_Y, x);
		}
	}

	input_mt_sync_frame(data->input);
	input_sync(data->input);

	return IRQ_HANDLED;
}
