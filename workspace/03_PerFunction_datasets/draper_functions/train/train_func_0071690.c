cavan_single_touch_device_create(void)
{
	struct cavan_single_touch_device *ts;
	struct cavan_touch_device *touch_dev;
	struct cavan_input_device *dev;

	ts = malloc(sizeof(*ts));
	if (ts == NULL)
	{
		pr_error_info("malloc");
		return NULL;
	}

	ts->pressed = 0;
	ts->point.pressed = false;

	touch_dev = &ts->touch_dev;
	touch_dev->xaxis = ABS_X;
	touch_dev->yaxis = ABS_Y;

	dev = &touch_dev->input_dev;
	dev->probe = cavan_single_touch_device_probe;
	dev->remove = NULL;
	dev->event_handler = cavan_single_touch_event_handler;

	return dev;
}
