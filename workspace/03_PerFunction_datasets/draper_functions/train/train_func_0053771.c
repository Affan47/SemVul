wacom_wac_finger_count_touches(struct wacom_wac *wacom)
{
	struct input_dev *input = wacom->touch_input;
	unsigned touch_max = wacom->features.touch_max;
	int count = 0;
	int i;

	if (!touch_max)
		return 0;

	if (touch_max == 1)
		return test_bit(BTN_TOUCH, input->key) &&
		       !wacom->shared->stylus_in_proximity;

	for (i = 0; i < input->mt->num_slots; i++) {
		struct input_mt_slot *ps = &input->mt->slots[i];
		int id = input_mt_get_value(ps, ABS_MT_TRACKING_ID);
		if (id >= 0)
			count++;
	}

	return count;
}
