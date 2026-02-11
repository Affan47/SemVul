input_mt_init_slots(struct input_dev *dev, unsigned int num_slots,
			unsigned int flags)
{
	struct input_mt *mt = dev->mt;
	int i;

	if (!num_slots)
		return 0;
	if (mt)
		return mt->num_slots != num_slots ? -EINVAL : 0;

	mt = kzalloc(sizeof(*mt) + num_slots * sizeof(*mt->slots), GFP_KERNEL);
	if (!mt)
		goto err_mem;

	mt->num_slots = num_slots;
	mt->flags = flags;
	input_set_abs_params(dev, ABS_MT_SLOT, 0, num_slots - 1, 0, 0);
	input_set_abs_params(dev, ABS_MT_TRACKING_ID, 0, TRKID_MAX, 0, 0);

	if (flags & (INPUT_MT_POINTER | INPUT_MT_DIRECT)) {
		__set_bit(EV_KEY, dev->evbit);
		__set_bit(BTN_TOUCH, dev->keybit);

		copy_abs(dev, ABS_X, ABS_MT_POSITION_X);
		copy_abs(dev, ABS_Y, ABS_MT_POSITION_Y);
		copy_abs(dev, ABS_PRESSURE, ABS_MT_PRESSURE);
	}
	if (flags & INPUT_MT_POINTER) {
		__set_bit(BTN_TOOL_FINGER, dev->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		if (num_slots >= 3)
			__set_bit(BTN_TOOL_TRIPLETAP, dev->keybit);
		if (num_slots >= 4)
			__set_bit(BTN_TOOL_QUADTAP, dev->keybit);
		if (num_slots >= 5)
			__set_bit(BTN_TOOL_QUINTTAP, dev->keybit);
		__set_bit(INPUT_PROP_POINTER, dev->propbit);
	}
	if (flags & INPUT_MT_DIRECT)
		__set_bit(INPUT_PROP_DIRECT, dev->propbit);
	if (flags & INPUT_MT_SEMI_MT)
		__set_bit(INPUT_PROP_SEMI_MT, dev->propbit);
	if (flags & INPUT_MT_TRACK) {
		unsigned int n2 = num_slots * num_slots;
		mt->red = kcalloc(n2, sizeof(*mt->red), GFP_KERNEL);
		if (!mt->red)
			goto err_mem;
	}


	for (i = 0; i < num_slots; i++)
		input_mt_set_value(&mt->slots[i], ABS_MT_TRACKING_ID, -1);


	mt->frame = 1;

	dev->mt = mt;
	return 0;
err_mem:
	kfree(mt);
	return -ENOMEM;
}
