update_mt_state(struct libevdev *dev, const struct input_event *e)
{
	if (e->code == ABS_MT_SLOT && dev->num_slots > -1) {
		int i;
		dev->current_slot = e->value;

		for (i = ABS_MT_SLOT + 1; i <= ABS_MT_MAX; i++) {
			if (libevdev_has_event_code(dev, EV_ABS, i))
				dev->abs_info[i].value = *slot_value(dev, dev->current_slot, i);
		}

		return 0;
	} else if (dev->current_slot == -1)
		return 1;

	*slot_value(dev, dev->current_slot, e->code) = e->value;

	return 0;
}
