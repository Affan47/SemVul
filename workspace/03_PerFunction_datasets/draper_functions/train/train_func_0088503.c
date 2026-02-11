cavan_gsensor_create(void)
{
	struct cavan_gsensor_device *sensor;
	struct cavan_input_device *dev;
	struct cavan_input_message_vector *vector;

	sensor = malloc(sizeof(*sensor));
	if (sensor == NULL)
	{
		pr_error_info("malloc");
		return NULL;
	}

	vector = &sensor->vector;
	vector->x = vector->y = vector->z = 0;

	dev = &sensor->input_dev;
	dev->probe = NULL;
	dev->remove = NULL;
	dev->event_handler = cavan_gsensor_event_handler;

	return dev;
}
